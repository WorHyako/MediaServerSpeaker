#include "Config.hpp"

#include "Scopes/ManagementScope.hpp"
#include "Scopes/QuickButtonScope.hpp"

#include "Controls/ControlCreator.hpp"
#include "Controls/ManagementButton.hpp"
#include "Controls/ManagementTextableButton.hpp"
#include "Controls/QuickButton.hpp"

#include "Hierarchy/Files.hpp"
#include "Json/JsonContentKeys.hpp"

#include "Command/BaseCommand.hpp"

#include "WorLibrary/Json/JsonManager.hpp"

namespace {
    /**
     * @brief
     *
     * @param configName
     *
     * @author WorHyako
     */
    [[nodiscard]]
    nlohmann::json loadConfigFile(const std::string &configName) noexcept {
        auto config = Wor::Json::tryToLoadFile(configName);

        std::string headKey(Mss::System::getJsonHeadKey().data());
        if (config.empty() ||
            !config.contains(headKey) ||
            !config[headKey].is_array()) {
            return {};
        }
        return config;
    }

    /**
     * @brief
     *
     * @param configName
     *
     * @param json
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    bool saveConfigFile(const std::string &configName, nlohmann::json &json) noexcept {
        return Wor::Json::tryToSaveFile(configName, json.dump());
    }

    /**
     * @brief
     *
     * @param json
     *
     * @param control
     *
     * @author WorHyako
     */
    void acceptBaseParameters(const nlohmann::json &json, Mss::Gui::Controls::BaseControl *control) {
        try {
            std::string text = json.at(Mss::System::getJsonTextKey());
            control->setText(text);

            int xPos = json.at(Mss::System::getJsonPositionKey()).at("x");
            int yPos = json.at(Mss::System::getJsonPositionKey()).at("y");
            control->move(xPos, yPos);

            int xSize = json.at(Mss::System::getJsonSizeKey()).at("x");
            int ySize = json.at(Mss::System::getJsonSizeKey()).at("y");
            control->resize(xSize, ySize);

            std::string commandStr = json.at(Mss::System::getJsonCommandKey());
            auto command = new Mss::Backend::Command::BaseCommand;
            command->set(commandStr);
            control->setCommand(command);
        } catch (const nlohmann::json::exception &e) {
            std::printf("Error: %s\n Bad object dump: %s\n",
                        e.what(), std::string(json.dump()).c_str());
        }
    }

    /**
     * @brief
     *
     * @param json
     *
     * @param control
     *
     * @author WorHyako
     */
    void makeBaseParameters(nlohmann::json &json, Mss::Gui::Controls::BaseControl *control) {
        json[Mss::System::getJsonTextKey()] = control->getText();
        json[Mss::System::getJsonCommandKey()] = control->getCommand()->str();
        json[Mss::System::getJsonPositionKey()] = {{ "x", control->pos().x() },
                                                   { "y", control->pos().y() }};
        json[Mss::System::getJsonSizeKey()] = {{ "x", control->size().width() },
                                               { "y", control->size().height() }};
    }
}

/**
 * TODO: Extract save/load common parameters to method parseBaseParameters(), parseMovableParameters() & etc
 */

using namespace Mss::Gui::Controls::Config;
using namespace Mss::Gui::Controls;
using namespace Mss::Gui::Scopes;

template<class TControlType>
nlohmann::json Config::makeConfig(WorQWidgetPtrVec) noexcept {
    std::printf("Save method for ControlType = %s aren't ready yet\n", typeid(TControlType).name());
    return {};
}

template<class TControlType>
WorQWidgetPtrVec Config::parseConfig(const nlohmann::json &) noexcept {
    std::printf("Load method for ControlType = %s aren't ready yet\n", typeid(TControlType).name());
    return {};
}

template<class TScopeType>
WorQWidgetPtrVec Config::load(const std::string &) noexcept {
    std::printf("Load method for ScopeType = %s aren't ready yet\n", typeid(TScopeType).name());
    return {};
}

template<class TScopeType>
bool Config::save(const std::string &, const QWidget *) noexcept {
    std::printf("Save method for ScopeType = %s aren't ready yet\n", typeid(TScopeType).name());
    return {};
}

template<>
WorQWidgetPtrVec Config::parseConfig<ManagementButton>(const nlohmann::json &json) noexcept {
    using Creator = ControlCreator<ManagementButton>;

    if (json.empty()) {
        return {};
    }

    WorQWidgetPtrVec controls;
    controls.reserve(json.size());

    std::for_each(std::begin(json), std::end(json), [&controls](const nlohmann::json &each) {
        auto control = Creator::create();

        ::acceptBaseParameters(each, control.get());
        controls.push_back(std::move(control));
    });

    return controls;
}

template<>
WorQWidgetPtrVec Config::parseConfig<ManagementTextableButton>(const nlohmann::json &json) noexcept {
    using Creator = ControlCreator<ManagementTextableButton>;

    if (json.empty()) {
        return {};
    }

    WorQWidgetPtrVec controls;
    controls.reserve(json.size());

    std::for_each(std::begin(json), std::end(json), [&controls](const nlohmann::json &each) {
        auto control = Creator::create();

        ::acceptBaseParameters(each, control.get());
        controls.push_back(std::move(control));
    });

    return controls;
}

template<>
WorQWidgetPtrVec Config::parseConfig<QuickButton>(const nlohmann::json &json) noexcept {
    using Creator = ControlCreator<Controls::QuickButton>;

    if (json.empty()) {
        return {};
    }

    WorQWidgetPtrVec controls;
    controls.reserve(json.size());

    std::for_each(std::begin(json), std::end(json), [&controls](const nlohmann::json &each) {
        auto control = Creator::create();
        ::acceptBaseParameters(each, control.get());

        controls.push_back(std::move(control));
    });

    return controls;
}

template<>
WorQWidgetPtrVec Config::load<QuickButtonScope>(const std::string &) noexcept {
    return {};
}

template<>
nlohmann::json Config::makeConfig<ManagementButton>(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json fullConfig;
    std::for_each(std::begin(controls), std::end(controls), [&fullConfig](std::unique_ptr<QWidget> &each) {
        auto control = dynamic_cast<ManagementButton *>(each.release());
        nlohmann::json config;
        ::makeBaseParameters(config, control);
        fullConfig[Mss::System::getManagementButtonKey()].push_back(config);
    });
    return fullConfig;
}

template<>
nlohmann::json Config::makeConfig<ManagementTextableButton>(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json fullConfig;
    std::for_each(std::begin(controls), std::end(controls), [&fullConfig](std::unique_ptr<QWidget> &each) {
        auto control = dynamic_cast<ManagementTextableButton *>(each.release());
        nlohmann::json config;
        ::makeBaseParameters(config, control);
        fullConfig[Mss::System::getManagementTextableButtonKey()].push_back(config);
    });
    return fullConfig;
}

template<>
nlohmann::json Config::makeConfig<QuickButton>(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json fullConfig;
    std::for_each(std::begin(controls), std::end(controls), [&fullConfig](std::unique_ptr<QWidget> &each) {
        auto control = dynamic_cast<QuickButton *>(each.release());
        nlohmann::json config;
        ::makeBaseParameters(config, control);
        fullConfig[Mss::System::getQuickButtonKey()].push_back(config);
    });
    return fullConfig;
}

template<>
bool Config::save<ManagementScope>(const std::string &tabName, const QWidget *owner) noexcept {
    const auto scope = dynamic_cast<const ManagementScope *>(owner);
    if (!scope) {
        return false;
    }

    auto allControls = scope->children();

    WorQWidgetPtrVec mbControls;
    WorQWidgetPtrVec mtbControls;

    std::for_each(std::begin(allControls), std::end(allControls), [&mbControls, &mtbControls](QObject *each) {
        auto control = dynamic_cast<QWidget *>(each);
        if (dynamic_cast<const ManagementButton *>(each)) {
            std::printf("%s was tracked.\n", Mss::System::getManagementButtonKey().data());
            mbControls.emplace_back(control);
        } else if (dynamic_cast<const ManagementTextableButton *>(each)) {
            std::printf("%s was tracked.\n", Mss::System::getManagementTextableButtonKey().data());
            mtbControls.emplace_back(control);
        }
    });

    nlohmann::json fullConfig;

    nlohmann::json mbConfig = makeConfig<ManagementButton>(std::move(mbControls));
    nlohmann::json mtbConfig = makeConfig<ManagementTextableButton>(std::move(mtbControls));

    fullConfig[Mss::System::getJsonHeadKey()] = { mbConfig, mtbConfig };

    std::string configPath = Mss::System::getResourcePath().data() +
                             tabName + '/' +
                             Mss::System::getManagementScopeConfigName().data();
    return ::saveConfigFile(configPath, fullConfig);
}

template<>
WorQWidgetPtrVec Config::load<ManagementScope>(const std::string &tabName) noexcept {
    std::string configPath(Mss::System::getResourcePath().data()
                           + tabName + '/'
                           + Mss::System::getManagementScopeConfigName().data());

    auto config = ::loadConfigFile(configPath);
    if (config.empty() || !config.is_object()) {
        std::printf("Fail to parse management config.\n");
        return {};
    }
    try {
        config = config[Mss::System::getJsonHeadKey().data()];

    } catch (const nlohmann::json::exception &e) {
        std::printf("Fail to parse management config.\nError: %s\n", e.what());
        return {};
    }

    if (!config.is_array()) {
        std::printf("Fail to parse management config.\n");
        return {};
    }

    WorQWidgetPtrVec mbControls;
    WorQWidgetPtrVec mtbControls;

    std::for_each(std::begin(config), std::end(config), [&mbControls, &mtbControls](const nlohmann::json &each) {
        if (each.contains(Mss::System::getManagementButtonKey())) {
            mbControls = Config::parseConfig<ManagementButton>(each.at(Mss::System::getManagementButtonKey()));
            return;
        } else if (each.contains(Mss::System::getManagementTextableButtonKey())) {
            mtbControls = Config::parseConfig<ManagementTextableButton>(
                    each.at(Mss::System::getManagementTextableButtonKey()));
            return;
        }
    });

    WorQWidgetPtrVec controls;

    controls.reserve(std::size(mbControls) + std::size(mtbControls));
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mbControls)),
                    std::make_move_iterator(std::end(mbControls)));
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mtbControls)),
                    std::make_move_iterator(std::end(mtbControls)));

    mtbControls.clear();
    mbControls.clear();
    return controls;
}
