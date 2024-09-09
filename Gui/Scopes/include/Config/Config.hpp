#pragma once

#include <string>
#include <vector>
#include <memory>

#include <QWidget>

#include "nlohmann/json.hpp"

#include "spdlog/spdlog.h"

#include "Hierarchy/Files.hpp"
#include "Json/JsonContentKeys.hpp"
#include "Command/BaseCommand.hpp"
#include "Interfaces/IMovableControl.hpp"
#include "Creators/ControlCreator.hpp"

#include "Wor/Json/JsonManager.hpp"

namespace Mss::Gui::Scopes {

	using WorQWidgetPtr = std::unique_ptr<QWidget>;
	using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

	using WorBaseControl = Controls::IControl;
	using WorMovableBaseControl = Controls::IMovableControl;

	/**
	 *  @brief
	 *
	 *  @tparam TScopeType
	 *
	 *  @author WorHyako
	 */
	template <class TScopeType>
	class Config final {
	public:
		template <class TControlType>
		using Creator = Controls::ControlCreator<TControlType>;

		/**
		 * @brief Ctor.
		 */
		explicit Config(std::string tabName) noexcept;

		/**
		 * @brief
		 *
		 * @tparam TControlType
		 *
		 * @param controls
		 *
		 * @return
		 */
		template <class TControlType>
		[[nodiscard]]
		nlohmann::json makeConfig(WorQWidgetPtrVec controls) noexcept;

		/**
		 * @brief
		 *
		 * @tparam  TControlType
		 *
		 * @return
		 */
		template <class TControlType>
		[[nodiscard]]
		WorQWidgetPtrVec loadFromConfig() const noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		bool loadConfig() noexcept;

		/**
		 * @brief
		 *
		 * @tparam TControlType
		 *
		 * @param owner
		 */
		template <class TControlType>
		void addToConfig(const QWidget *owner) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		bool saveConfig() const noexcept;

	private:
		/**
		 * @brief
		 *
		 * @param json
		 *
		 * @param control
		 */
		void acceptBaseParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

		/**
		 * @brief
		 *
		 * @param json
		 *
		 * @param control
		 */
		void acceptMovableParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

		/**
		 * @brief
		 *
		 * @param json
		 *
		 * @param control
		 */
		void makeBaseParameters(nlohmann::json &json, WorBaseControl *control) noexcept;

		/**
		 * @brief
		 *
		 * @param json
		 *
		 * @param control
		 */
		void makeMovableParameters(nlohmann::json &json, WorBaseControl *control) noexcept;

		nlohmann::json _config;

		std::string _tabName;
	};

	template <class TScopeType>
	Config<TScopeType>::Config(std::string tabName) noexcept
		: _tabName(std::move(tabName)) {
	}

	template <class TScopeType>
	template <class TControlType>
	WorQWidgetPtrVec Config<TScopeType>::loadFromConfig() const noexcept {
		auto it = std::find_if(std::begin(_config),
							   std::end(_config),
							   [](const nlohmann::json &each) {
								   return each.contains(System::jsonControlKey<TControlType>());
							   });
		if (it == _config.end()) {
			return {};
		}

		auto typeConfig = (*it).at(System::jsonControlKey<TControlType>());
		WorQWidgetPtrVec controls;
		std::ranges::for_each(typeConfig,
							  [this, &controls](const nlohmann::json &each) {
								  auto control = Creator<TControlType>::create();
								  acceptBaseParameters(each, control.get());

								  if (dynamic_cast<WorMovableBaseControl *>(control.get())) {
									  acceptMovableParameters(each, control.get());
								  }

								  controls.push_back(std::move(control));
							  });
		return controls;
	}

	template <class TScopeType>
	template <class TControlType>
	void Config<TScopeType>::addToConfig(const QWidget *owner) noexcept {
		const auto scope = dynamic_cast<const TScopeType *>(owner);
		if (!scope) {
			return;
		}

		auto allControls = scope->children();

		WorQWidgetPtrVec controls;
		controls.reserve(allControls.size());

		std::ranges::for_each(allControls,
							  [&controls](QObject *each) {
								  auto control = dynamic_cast<QWidget *>(each);
								  if (dynamic_cast<const TControlType *>(each)) {
									  std::stringstream ss;
									  ss << "Config generation: "
											  << System::jsonControlKey<TControlType>().data()
											  << "was tracked.";
									  spdlog::info(ss.str());
									  controls.emplace_back(control);
								  }
							  });

		nlohmann::json config = makeConfig<TControlType>(std::move(controls));

		_config[System::jsonHeadKey()].emplace_back(std::move(config));
	}

	template <class TScopeType>
	template <class TControlType>
	nlohmann::json Config<TScopeType>::makeConfig(WorQWidgetPtrVec controls) noexcept {
		nlohmann::json fullConfig;
		std::ranges::for_each(controls,
							  [this, &fullConfig](std::unique_ptr<QWidget> &each) {
								  auto control = dynamic_cast<TControlType *>(each.release());
								  if (!control) {
									  return;
								  }
								  nlohmann::json config;
								  makeBaseParameters(config, control);

								  if (dynamic_cast<WorMovableBaseControl *>(control)) {
									  makeMovableParameters(config, control);
								  }
								  fullConfig[System::jsonControlKey<TControlType>()].push_back(std::move(config));
							  });
		return fullConfig;
	}

	template <class TScopeType>
	bool Config<TScopeType>::saveConfig() const noexcept {
		std::string configPath = System::getResourcePath().data() +
				_tabName + '/' +
				System::getConfigName<TScopeType>().data();
		return Wor::Json::tryToSaveFile(configPath, _config.dump());
	}

	template <class TScopeType>
	bool Config<TScopeType>::loadConfig() noexcept {
		const std::string configPath(System::getResourcePath().data()
				+ _tabName + '/'
				+ System::getConfigName<TScopeType>().data());

		auto config = Wor::Json::tryToLoadFile(configPath);

		if (config.empty()
			|| !config.contains(System::jsonHeadKey().data())) {
			std::stringstream ss;
			ss << "Failed to parse config from resource path: "
					<< configPath;
			spdlog::error(ss.str());
			return false;
		}
		_config = config.at(System::jsonHeadKey().data());
		std::stringstream ss;
		ss << "Success to parse config from resource path: "
				<< configPath;
		spdlog::info(ss.str());
		return true;
	}

	template <class TScopeType>
	void Config<TScopeType>::acceptBaseParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept {
		try {
			std::string text = json.at(System::jsonTextKey());
			control->text(std::move(text));

			std::string sessionName = json.at(System::jsonSessionNameKey());
			control->sessionName(std::move(sessionName));

			std::uint8_t midiButtonId = json.at(System::jsonMidiButtonIdKey());
			control->midiKeyIdx(midiButtonId);
			control->createServerRoad();

			std::string commandStr = json.at(System::jsonCommandKey());
			auto command = new Backend::Command::BaseCommand;
			command->set(commandStr);
			control->command(command);
		} catch (const nlohmann::json::exception &e) {
			std::stringstream ss;
			ss << "Config loading:\nBad config: "
					<< json.dump()
					<< "\nError info: "
					<< e.what();
			spdlog::error(ss.str());
		}
	}

	template <class TScopeType>
	void Config<TScopeType>::acceptMovableParameters(const nlohmann::json &json,
													 WorBaseControl *control) const noexcept {
		try {
			int xPos = json.at(System::jsonPositionKey()).at("x");
			int yPos = json.at(System::jsonPositionKey()).at("y");
			control->move(xPos, yPos);

			int xSize = json.at(System::jsonSizeKey()).at("x");
			int ySize = json.at(System::jsonSizeKey()).at("y");
			control->resize(xSize, ySize);
		} catch (const nlohmann::json::exception &e) {
			std::stringstream ss;
			ss << "Config loading:\nBad config: "
					<< json.dump()
					<< "\nError info: "
					<< e.what();
			spdlog::error(ss.str());
		}
	}

	template <class TScopeType>
	void Config<TScopeType>::makeBaseParameters(nlohmann::json &json, WorBaseControl *control) noexcept {
		json[System::jsonTextKey()] = control->text();
		json[System::jsonCommandKey()] = control->command()->str();
		json[System::jsonSessionNameKey()] = control->sessionName();
		json[System::jsonMidiButtonIdKey()] = control->midiKeyIdx();
	}

	template <class TScopeType>
	void Config<TScopeType>::makeMovableParameters(nlohmann::json &json, WorBaseControl *control) noexcept {
		json[System::jsonPositionKey()] = {{"x", control->pos().x()},
										   {"y", control->pos().y()}};
		json[System::jsonSizeKey()] = {{"x", control->size().width()},
									   {"y", control->size().height()}};
	}
}
