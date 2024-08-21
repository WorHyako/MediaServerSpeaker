#pragma once

#include <string>
#include <vector>
#include <memory>

#include <QWidget>

#include "nlohmann/json.hpp"

#include "Hierarchy/Files.hpp"
#include "Json/JsonContentKeys.hpp"
#include "Command/BaseCommand.hpp"

#include "Controls/MovableBaseControl.hpp"
#include "Creators/ControlCreator.hpp"

#include "Json/JsonManager.hpp"

namespace Mss::Gui::Scopes {

	using WorQWidgetPtr = std::unique_ptr<QWidget>;
	using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

	using WorBaseControl = Mss::Gui::Controls::BaseControl;
	using WorMovableBaseControl = Mss::Gui::Controls::MovableBaseControl;

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
		using Creator = Mss::Gui::Controls::ControlCreator<TControlType>;

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
		 * @param tabName
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
		 * @param tabName
		 *
		 * @param owner
		 */
		template <class TControlType>
		void addToConfig(const QWidget *owner) noexcept;

		/**
		 * @brief
		 *
		 * @param tabName
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
		: _tabName(std::move(tabName)),
		  _config() {
	}

	template <class TScopeType>
	template <class TControlType>
	WorQWidgetPtrVec Config<TScopeType>::loadFromConfig() const noexcept {
		auto it = std::find_if(std::begin(_config),
							   std::end(_config),
							   [](const nlohmann::json &each) {
								   return each.contains(Mss::System::jsonControlKey<TControlType>());
							   });
		if (it == _config.end()) {
			return {};
		}

		auto typeConfig = (*it).at(Mss::System::jsonControlKey<TControlType>());
		WorQWidgetPtrVec controls;
		std::for_each(std::begin(typeConfig),
					  std::end(typeConfig),
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

		std::for_each(std::begin(allControls),
					  std::end(allControls),
					  [&controls](QObject *each) {
						  auto control = dynamic_cast<QWidget *>(each);
						  if (dynamic_cast<const TControlType *>(each)) {
							  std::printf("%s was tracked.\n", Mss::System::jsonControlKey<TControlType>().data());
							  controls.emplace_back(control);
						  }
					  });

		nlohmann::json config = makeConfig<TControlType>(std::move(controls));

		_config[Mss::System::jsonHeadKey()].emplace_back(std::move(config));
	}

	template <class TScopeType>
	template <class TControlType>
	nlohmann::json Config<TScopeType>::makeConfig(WorQWidgetPtrVec controls) noexcept {
		nlohmann::json fullConfig;
		std::for_each(std::begin(controls),
					  std::end(controls),
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
						  fullConfig[Mss::System::jsonControlKey<TControlType>()].push_back(std::move(config));
					  });
		return fullConfig;
	}

	template <class TScopeType>
	bool Config<TScopeType>::saveConfig() const noexcept {
		std::string configPath = Mss::System::getResourcePath().data() +
				_tabName + '/' +
				Mss::System::getConfigName<TScopeType>().data();
		return Wor::Json::tryToSaveFile(configPath, _config.dump());
	}

	template <class TScopeType>
	bool Config<TScopeType>::loadConfig() noexcept {
		std::string configPath(Mss::System::getResourcePath().data()
				+ _tabName + '/'
				+ Mss::System::getConfigName<TScopeType>().data());

		auto config = Wor::Json::tryToLoadFile(configPath);

		if (config.empty()
			|| !config.contains(Mss::System::jsonHeadKey().data())) {
			std::printf("Fail to parse config: %s\n", configPath.c_str());
			return false;
		}
		_config = config.at(Mss::System::jsonHeadKey().data());
		return true;
	}

	template <class TScopeType>
	void Config<TScopeType>::acceptBaseParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept {
		try {
			std::string text = json.at(Mss::System::jsonTextKey());
			control->text(text);

			std::string sessionName = json.at(Mss::System::jsonSessionNameKey());
			control->sessionName(sessionName);

			std::string commandStr = json.at(Mss::System::jsonCommandKey());
			auto command = new Mss::Backend::Command::BaseCommand;
			command->set(commandStr);
			control->command(command);
		} catch (const nlohmann::json::exception &e) {
			std::printf("Error: %s\n Bad object dump: %s\n",
						e.what(),
						std::string(json.dump()).c_str());
		}
	}

	template <class TScopeType>
	void Config<
		TScopeType>::acceptMovableParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept {
		try {
			int xPos = json.at(Mss::System::jsonPositionKey()).at("x");
			int yPos = json.at(Mss::System::jsonPositionKey()).at("y");
			control->move(xPos, yPos);

			int xSize = json.at(Mss::System::jsonSizeKey()).at("x");
			int ySize = json.at(Mss::System::jsonSizeKey()).at("y");
			control->resize(xSize, ySize);
		} catch (const nlohmann::json::exception &e) {
			std::printf("Error: %s\n Bad object dump: %s\n",
						e.what(),
						std::string(json.dump()).c_str());
		}
	}

	template <class TScopeType>
	void Config<TScopeType>::makeBaseParameters(nlohmann::json &json, WorBaseControl *control) noexcept {
		json[Mss::System::jsonTextKey()] = control->text();
		json[Mss::System::jsonCommandKey()] = control->command()->str();
		json[Mss::System::jsonSessionNameKey()] = control->sessionName();
	}

	template <class TScopeType>
	void Config<TScopeType>::makeMovableParameters(nlohmann::json &json, WorBaseControl *control) noexcept {
		json[Mss::System::jsonPositionKey()] = {{"x", control->pos().x()},
												{"y", control->pos().y()}};
		json[Mss::System::jsonSizeKey()] = {{"x", control->size().width()},
											{"y", control->size().height()}};
	}
}
