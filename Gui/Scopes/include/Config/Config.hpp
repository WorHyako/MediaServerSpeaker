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

	/**
	 * @brief Unique pointer to QWidget.
	 */
	using WorQWidgetPtr = std::unique_ptr<QWidget>;

	/**
	 * @brief Vector of unique pointer to QWidget.
	 */
	using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

	/**
	 * @brief Short naming of Control::IControl.
	 */
	using WorBaseControl = Controls::IControl;

	/**
	 * @brief Short naming of Controls::IMovableControl.
	 */
	using WorMovableBaseControl = Controls::IMovableControl;

	/**
	 *  @brief		Object to collect controls from Wor scope and save/load config.
	 *				<p>
	 *				Each public method logs process.
	 *				<p>
	 *				Working directory forming as @code System::getResourcePath()/tabName/scopeName.json @endcode
	 *	@usage
	 *	@code
	 *				/// Loading example
	 *				Config<WorScopeType> config(tabName);
	 *				if (!config.loadConfig()) {
	 *					...
	 *				}
	 *				auto controls = config.loadFromConfig<WorControlType>();
	 *
	 *				/// Saving example
	 *				Config<WorScopeType> config(tabName);
	 *				config.addToConfig<WorControlType1>(this);
	 *				config.addToConfig<WorControlType2>(this);
	 *				auto result = config.saveConfig();
	 *	@endcode
	 *
	 *  @tparam		TScopeType	Scope type to collect controls.
	 *
	 *  @author		WorHyako
	 *
	 *  @remark		I don't recommend u to see class implementation.
	 *				<p>
	 *				Take your time and think one more time.
	 */
	template <class TScopeType>
	class Config final {
	public:
		/**
		 * @brief	Short Creator name for current control type.
		 *
		 * @see		@code Controls::ControlCreator @endcode
		 */
		template <class TControlType>
		using Creator = Controls::ControlCreator<TControlType>;

		/**
		 * @brief	Ctor.
		 *
		 * @param	tabName	Tab's name. It uses in config forming.
		 */
		explicit Config(std::string tabName) noexcept;

		/**
		 * @brief	Tries to load config file.
		 *			Config file should have @code System::jsonHeadKey() @endcode json root key.
		 *			<p>
		 *			See config filepath in class description.
		 *			<p>
		 *			Each control will be created via @code Config::Creator @endcode.
		 *
		 * @return	@code true @endcode		Config file was loaded and ready to use.
		 *			<p>
		 *			@code false @endcode	Error in config file loading.
		 */
		[[nodiscard]]
		bool loadConfig() noexcept;

		/**
		 * @brief	Loads controls from current config.
		 *			<p>
		 *			Requires loaded config via @code loadConfig() @endcode method.
		 *
		 * @tparam  TControlType	Wor control type to load from config.
		 *
		 * @return	List of loaded controls.
		 */
		template <class TControlType>
		[[nodiscard]]
		WorQWidgetPtrVec loadFromConfig() const noexcept;

		/**
		 * @brief	Parses @code owner @endcode to collect controls and add them to config.
		 *
		 * @tparam	TControlType	Wor controls type to collect.
		 *
		 * @param	owner			Pointer to wor scope which contains controls to collect.
		 */
		template <class TControlType>
		void addToConfig(const QWidget *owner) noexcept;

		/**
		 * @brief			Tries to save current config.
		 *					<p>
		 *					See config filepath in class description.
		 *
		 * Config pattern
		 * @code
		 *					"Control name": [
		 *					{
		 *						"command": "<tag key=\"value\" .../>\n",
		 *						"position": {
		 *							"x": ...,
		 *							"y": ...
		 *						},
		 *						"sessionName": "...",
		 *						"size": {
		 *							"x": ...,
		 *							"y": ...
		 *						},
		 *						"text": "..."
		 *					}
		 * @endcode
		 *
		 * @return			@code true @endcode		Error on saving process.
		 *					<p>
		 *					@code false @endcode	Saving process done.
		 *
		 * @see				@code Wor::Json::tryToSaveFile @endcode
		 */
		[[nodiscard]]
		bool saveConfig() const noexcept;

	private:
		/**
		 * @brief	Generates config object from selected control.
		 *			<p>
		 *			Works with @code IControls @endcode and @code IMovableControl @endcode.
		 *
		 * @tparam	TControlType	Wor control type.
		 *
		 * @param	controls		Control list to form config.
		 *
		 * @return	Config via json object.
		 */
		template <class TControlType>
		[[nodiscard]]
		nlohmann::json makeConfig(WorQWidgetPtrVec controls) noexcept;

		/**
		 * @brief	Accepts config's data to selected control.
		 *			<p>
		 *			Accepts only base data for IControl's fields.
		 *			<p>
		 *			Logs process.
		 *
		 * @param	json	Config's part object for current control.
		 *
		 * @param	control	Control to accept data from config.
		 */
		void acceptBaseParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

		/**
		 * @brief	Accepts config's data to selected control.
		 *			<p>
		 *			Accepts only data for IMovableControl's fields.
		 *			<p>
		 *			Logs process.
		 *
		 * @param	json	Config's part object for current control.
		 *
		 * @param	control	Control to accept data from config.
		 */
		void acceptMovableParameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

		/**
		 * @brief	Parses control's fields to form config's part object.
		 *			<p>
		 *			Parses only data from @code IControl @endcode fields.
		 *
		 * @param	json	Config's part object for current control.
		 *
		 * @param	control Control to parse data for config.
		 */
		void makeBaseParameters(nlohmann::json &json, WorBaseControl *control) noexcept;

		/**
		 * @brief	Parses control's fields to form config's part object.
		 *			<p>
		 *			Parses only data from @code IMovableControl @endcode fields.
		 *
		 * @param	json	Config's part object for current control.
		 *
		 * @param	control Control to parse data for config.
		 */
		void makeMovableParameters(nlohmann::json &json, WorBaseControl *control) noexcept;

		/**
		 * @brief Store full config object.
		 */
		nlohmann::json _config;

		/**
		 * @brief Tab name uses in json scope naming.
		 */
		std::string _tabName;
	};

	template <class TScopeType>
	Config<TScopeType>::Config(std::string tabName) noexcept
		: _tabName(std::move(tabName)) {
	}

	template <class TScopeType>
	template <class TControlType>
	WorQWidgetPtrVec Config<TScopeType>::loadFromConfig() const noexcept {
		auto it = std::ranges::find_if(_config,
									   [](const nlohmann::json &each) {
										   return each.contains(System::jsonControlKey<TControlType>());
									   });
		if (it == std::end(_config)) {
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
