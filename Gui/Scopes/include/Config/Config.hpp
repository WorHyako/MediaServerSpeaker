#pragma once

#include "Command/BaseCommand.hpp"
#include "Creators/ControlCreator.hpp"
#include "Hierarchy/Files.hpp"
#include "Interfaces/IMovableControl.hpp"
#include "Json/JsonContentKeys.hpp"

#include "Wor/Json/JsonManager.hpp"

#include <memory>
#include <string>
#include <vector>

#include <QWidget>

#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

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
 *  @brief Object to collect controls from Wor scope and save/load config.
 *
 * Each public method logs process.
 *
 * Working directory forming as @code System::getResourcePath()/tabName/scopeName.json
 *
 * @usage
 * @code
 *     /// Loading example
 *     Config<WorScopeType> config(tabName);
 *     if (!config.loadConfig()) {
 *         ...
 *     }
 *     auto controls = config.loadFromConfig<WorControlType>();
 *
 *     /// Saving example
 *     Config<WorScopeType> config(tabName);
 *     config.addToConfig<WorControlType1>(this);
 *     config.addToConfig<WorControlType2>(this);
 *     auto result = config.saveConfig();
 * @endcode
 *
 * @tparam TScopeType Scope type to collect controls.
 *
 * @author WorHyako
 *
 * @remark I don't recommend u to see class implementation.
 *
 * Take your time and think one more time.
 */
template <class TScopeType>
class Config final {
public:
    /**
     * @brief Short Creator name for current control type.
     *
     * @see Controls::ControlCreator.
     */
    template <class TControlType>
    using Creator = Controls::ControlCreator<TControlType>;

    /**
     * @brief Constructor.
     *
     * @param tab_name Tab's name. It uses in config forming.
     */
    explicit Config(std::string tab_name) noexcept;

    /**
     * @brief Tries to load config file.
     * Config file should have System::jsonHeadKey() json root key.
     *
     * See config filepath in class description.
     *
     * Each control will be created via Config::Creator.
     *
     * @return true Config file was loaded and ready to use.
     * @return false Error in config file loading.
     */
    [[nodiscard]]
    bool load_config() noexcept;

    /**
     * @brief Loads controls from current config.
     *
     * Requires pre-loaded config via loadConfig() method.
     *
     * @tparam TControlType Wor control type to load from config.
     *
     * @return List of loaded controls.
     */
    template <class TControlType>
    [[nodiscard]]
    WorQWidgetPtrVec load_from_config() const noexcept;

    /**
     * @brief Parses owner to collect controls and add them to config.
     *
     * @tparam TControlType Wor controls type to collect.
     *
     * @param owner Pointer to wor scope which contains controls to collect.
     */
    template <class TControlType>
    void add_to_config(const QWidget *owner) noexcept;

    /**
     * @brief Tries to save current config.
     *
     * See config filepath in class description.
     *
     * Config pattern
     * @code
     *     "Control name": [
     *	   {
     *         "command": "<tag key=\"value\" .../>\n",
     *         "position": {
     *             "x": ...,
     *             "y": ...
     *         },
     *         "sessionName": "...",
     *         "size": {
     *             "x": ...,
     *             "y": ...
     *         },
     *         "text": "..."
     * }
     * @endcode
     *
     * @return true Error on saving process.
     *
     * @return false Saving process done.
     *
     * @see Wor::Json::tryToSaveFile.
     */
    [[nodiscard]]
    bool save_config() const noexcept;

private:
    /**
     * @brief Generates config object from selected control.
     *
     * Works with IControls and IMovableControl.
     *
     * @tparam TControlType Wor control type.
     *
     * @param controls Control list to form config.
     *
     * @return Config via json object.
     */
    template <class TControlType>
    [[nodiscard]]
    nlohmann::json make_config(WorQWidgetPtrVec controls) noexcept;

    /**
     * @brief Accepts config's data to selected control.
     *
     * Accepts only base data for IControl's fields.
     *
     * Logs process.
     *
     * @param json Config's part object for current control.
     *
     * @param control Control to accept data from config.
     */
    void accept_base_parameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

    /**
     * @brief Accepts config's data to selected control.
     *
     * Accepts only data for IMovableControl's fields.
     *
     * Logs process.
     *
     * @param json Config's part object for current control.
     *
     * @param control Control to accept data from config.
     */
    void accept_movable_parameters(const nlohmann::json &json, WorBaseControl *control) const noexcept;

    /**
     * @brief Parses control's fields to form config's part object.
     *
     * Parses only data from @code IControl @endcode fields.
     *
     * @param json Config's part object for current control.
     *
     * @param control Control to parse data for config.
     */
    void make_base_parameters(nlohmann::json &json, WorBaseControl *control) noexcept;

    /**
     * @brief Parses control's fields to form config's part object.
     *
     * Parses only data from @code IMovableControl @endcode fields.
     *
     * @param json Config's part object for current control.
     *
     * @param control Control to parse data for config.
     */
    void make_movable_parameters(nlohmann::json &json, WorBaseControl *control) noexcept;

    /**
     * @brief Store full config object.
     */
    nlohmann::json config_;

    /**
     * @brief Tab name uses in json scope naming.
     */
    std::string tab_name_;
};

template <class TScopeType>
Config<TScopeType>::Config(std::string tab_name) noexcept
    : tab_name_{ std::move(tab_name) } {
}

template <class TScopeType>
template <class TControlType>
WorQWidgetPtrVec Config<TScopeType>::load_from_config() const noexcept {
    auto it{ std::ranges::find_if(config_,
                                  [](const nlohmann::json &each) {
                                      return each.contains(System::json_control_key<TControlType>());
                                  }) };
    if (it == std::end(config_)) {
        return {};
    }

    auto type_config{ (*it).at(System::json_control_key<TControlType>()) };
    WorQWidgetPtrVec controls;
    std::ranges::for_each(type_config,
                          [this, &controls](const nlohmann::json &each) {
                              auto control{ Creator<TControlType>::create() };
                              accept_base_parameters(each, control.get());

                              if (dynamic_cast<WorMovableBaseControl *>(control.get())) {
                                  accept_movable_parameters(each, control.get());
                              }

                              controls.push_back(std::move(control));
                          });
    return controls;
}

template <class TScopeType>
template <class TControlType>
void Config<TScopeType>::add_to_config(const QWidget *owner) noexcept {
    const auto scope{ dynamic_cast<const TScopeType *>(owner) };
    if (!scope) {
        return;
    }

    auto all_controls{ scope->children() };

    WorQWidgetPtrVec controls;
    controls.reserve(std::size(all_controls));

    std::ranges::for_each(all_controls,
                          [&controls](QObject *each) {
                              auto control{ dynamic_cast<QWidget *>(each) };
                              if (dynamic_cast<const TControlType *>(each)) {
                                  std::stringstream ss;
                                  ss << "Config generation: " << System::json_control_key<TControlType>().data() <<
                                      "was tracked.";
                                  spdlog::info(ss.str());
                                  controls.emplace_back(control);
                              }
                          });

    nlohmann::json config{ make_config<TControlType>(std::move(controls)) };

    config_[System::json_head_key()].emplace_back(std::move(config));
}

template <class TScopeType>
template <class TControlType>
nlohmann::json Config<TScopeType>::make_config(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json full_config;
    std::ranges::for_each(controls,
                          [this, &full_config](std::unique_ptr<QWidget> &each) {
                              auto control{ dynamic_cast<TControlType *>(each.release()) };
                              if (!control) {
                                  return;
                              }
                              nlohmann::json config;
                              make_base_parameters(config, control);

                              if (dynamic_cast<WorMovableBaseControl *>(control)) {
                                  make_movable_parameters(config, control);
                              }
                              full_config[System::json_control_key<TControlType>()].push_back(std::move(config));
                          });
    return full_config;
}

template <class TScopeType>
bool Config<TScopeType>::save_config() const noexcept {
    const std::string configPath{ System::get_resource_path().data() + tab_name_ + '/' +
                                  System::get_config_name<TScopeType>().data() };
    return Wor::Json::tryToSaveFile(configPath, config_.dump());
}

template <class TScopeType>
bool Config<TScopeType>::load_config() noexcept {
    const std::string configPath{ System::get_resource_path().data() + tab_name_ + '/' +
                                  System::get_config_name<TScopeType>().data() };

    auto config{ Wor::Json::tryToLoadFile(configPath) };

    if (config.empty() || !config.contains(System::json_head_key().data())) {
        std::stringstream ss;
        ss << "Failed to parse config from resource path: " << configPath;
        spdlog::error(ss.str());
        return false;
    }
    config_ = config.at(System::json_head_key().data());
    std::stringstream ss;
    ss << "Success to parse config from resource path: " << configPath;
    spdlog::info(ss.str());
    return true;
}

template <class TScopeType>
void Config<TScopeType>::accept_base_parameters(const nlohmann::json &json, WorBaseControl *control) const noexcept {
    try {
        std::string text{ json.at(System::json_text_key()) };
        control->set_text(std::move(text));

        std::string session_name{ json.at(System::json_session_name_key()) };
        control->set_session_name(std::move(session_name));

        std::uint8_t midi_button_id{ json.at(System::json_midi_button_id_key()) };
        control->set_midi_key_idx(midi_button_id);
        control->create_server_road();

        std::string command_str{ json.at(System::json_command_key()) };
        auto command{ new Backend::Command::BaseCommand };
        command->set(command_str);
        control->command(command);
    } catch (const nlohmann::json::exception &e) {
        std::stringstream ss;
        ss << "Config loading:\nBad config: " << json.dump() << "\nError info: " << e.what();
        spdlog::error(ss.str());
    }
}

template <class TScopeType>
void Config<TScopeType>::accept_movable_parameters(const nlohmann::json &json, WorBaseControl *control) const noexcept {
    try {
        const int x_pos{ json.at(System::json_position_key()).at("x") };
        const int y_pos{ json.at(System::json_position_key()).at("y") };
        control->move(x_pos, y_pos);

        const int x_size{ json.at(System::json_size_key()).at("x") };
        const int y_size{ json.at(System::json_size_key()).at("y") };
        control->resize(x_size, y_size);
    } catch (const nlohmann::json::exception &e) {
        std::stringstream ss;
        ss << "Config loading:\nBad config: " << json.dump() << "\nError info: " << e.what();
        spdlog::error(ss.str());
    }
}

template <class TScopeType>
void Config<TScopeType>::make_base_parameters(nlohmann::json &json, WorBaseControl *control) noexcept {
    json[System::json_text_key()] = control->get_text();
    json[System::json_command_key()] = control->command()->str();
    json[System::json_session_name_key()] = control->get_session_name();
    json[System::json_midi_button_id_key()] = control->get_midi_key_idx();
}

template <class TScopeType>
void Config<TScopeType>::make_movable_parameters(nlohmann::json &json, WorBaseControl *control) noexcept {
    json[System::json_position_key()] = {
        { "x", control->pos().x() },
        { "y", control->pos().y() }
    };
    json[System::json_size_key()] = {
        { "x", control->size().width() },
        { "y", control->size().height() }
    };
}
}
