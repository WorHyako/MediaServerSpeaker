#include "Config.hpp"

#include "Scopes/ManagementScope.hpp"
#include "Scopes/QuickButtonScope.hpp"

#include "Controls/ControlCreator.hpp"
#include "Controls/ManagementButton.hpp"
#include "Controls/QuickButton.hpp"

#include "Hierarchy/Files.hpp"
#include "Json/JsonContentKeys.hpp"

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

        const auto headKey = std::string(Mss::System::getJsonHeadKey());
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
}

using namespace Mss::Gui::Controls::Config;
using namespace Mss::Gui::Controls;
using namespace Mss::Gui::Scopes;

template<class TControlType>
nlohmann::json Config::saveControls(WorQWidgetPtrVec) noexcept {
    std::printf("Save method for ControlType = %s aren't ready yet", typeid(TControlType).name());
    return {};
}

template<class TControlType>
WorQWidgetPtrVec Config::loadControls(const nlohmann::json &) noexcept {
    std::printf("Load method for ControlType = %s aren't ready yet", typeid(TControlType).name());
    return {};
}

template<class TScopeType>
WorQWidgetPtrVec Config::load(const std::string &) noexcept {
    std::printf("Load method for ScopeType = %s aren't ready yet",
                typeid(TScopeType).name());
    return {};
}

template<class TScopeType>
bool Config::save(const std::string &, const QWidget *) noexcept {
    std::printf("Save method for ScopeType = %s aren't ready yet", typeid(TScopeType).name());
    return {};
}

template<>
WorQWidgetPtrVec Config::loadControls<ManagementButton>(const nlohmann::json &json) noexcept {
    using Creator = ControlCreator<ManagementButton>;

    if (json.empty()) {
        return {};
    }

    WorQWidgetPtrVec controls;
    controls.reserve(json.size());

    std::for_each(std::begin(json), std::end(json), [&controls](const nlohmann::json &each) {
        auto button = Creator::create();
        try {
            std::string text = each.at(Mss::System::getJsonTextKey());
            button->setText(text);
            bool canMove = each.at(Mss::System::getJsonCanMoveKey());
            button->setCanMove(canMove);
            bool canResize = each.at(Mss::System::getJsonCanResizeKey());
            button->setCanResize(canResize);
            int xPos = each.at(Mss::System::getJsonPositionKey()).at("x");
            int yPos = each.at(Mss::System::getJsonPositionKey()).at("y");
            button->move(xPos, yPos);
            int xSize = each.at(Mss::System::getJsonSizeKey()).at("x");
            int ySize = each.at(Mss::System::getJsonSizeKey()).at("y");
            button->resize(xSize, ySize);
        } catch (const nlohmann::json::exception &e) {
            std::printf("Error: %s\n Bad object dump: %s\n",
                        e.what(), std::string(each.dump()).c_str());
            return;
        }
        controls.push_back(std::move(button));
    });

    return controls;
}

template<>
WorQWidgetPtrVec Config::loadControls<QuickButton>(const nlohmann::json &json) noexcept {
    using Creator = ControlCreator<Controls::QuickButton>;

    if (json.empty()) {
        return {};
    }

    WorQWidgetPtrVec controls;
    controls.reserve(json.size());

    std::for_each(std::begin(json), std::end(json), [&controls](const nlohmann::json &each) {
        auto button = Creator::create();
        try {
            std::string text = each.at(Mss::System::getJsonTextKey());
            button->setText(text);
            int xPos = each.at(Mss::System::getJsonPositionKey()).at("x");
            int yPos = each.at(Mss::System::getJsonPositionKey()).at("y");
            button->move(xPos, yPos);
            int xSize = each.at(Mss::System::getJsonSizeKey()).at("x");
            int ySize = each.at(Mss::System::getJsonSizeKey()).at("y");
            button->resize(xSize, ySize);
        } catch (const nlohmann::json::exception &e) {
            std::printf("Error: %s\n Bad object dump: %s\n",
                        e.what(), std::string(each.dump()).c_str());
            return;
        }
        controls.push_back(std::move(button));
    });

    return controls;
}

template<>
WorQWidgetPtrVec Config::load<QuickButtonScope>(const std::string &) noexcept {
    return {};
}

template<>
WorQWidgetPtrVec Config::load<ManagementScope>(const std::string &tabName) noexcept {
    std::string tabPath = std::string(Mss::System::getResourcePath()) + tabName + '/';

    std::string configPath(tabPath + std::string(Mss::System::getManagementScopeConfigName()));

    auto config = ::loadConfigFile(configPath);
    if (config.empty() || !config.is_object()) {
        std::printf("Fail to parse management config.\n");
        return {};
    }
    config = config[std::string(Mss::System::getJsonHeadKey())];
    if (!config.is_array()) {
        std::printf("Fail to parse management config.\n");
        return {};
    }

    WorQWidgetPtrVec mbControls;
    WorQWidgetPtrVec qbControls;

    std::for_each(std::begin(config), std::end(config), [&mbControls, &qbControls](const nlohmann::json &each) {
        if (each.contains(Mss::System::getManagementButtonKey())) {
            mbControls = Config::loadControls<ManagementButton>(each.at(Mss::System::getManagementButtonKey()));
            return;
        } else if (each.contains(Mss::System::getQuickButtonKey())) {
            qbControls = Config::loadControls<QuickButton>(each.at(Mss::System::getQuickButtonKey()));
            return;
        }
    });

    WorQWidgetPtrVec controls;

    controls.reserve(mbControls.size() + qbControls.size());
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mbControls)), std::make_move_iterator(std::end(mbControls)));

    qbControls.clear();
    mbControls.clear();
    return controls;
}

template<>
nlohmann::json Config::saveControls<ManagementButton>(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json fullConfig;
    constexpr std::string_view type = "Management Button";
    std::for_each(std::begin(controls), std::end(controls), [&fullConfig, &type](std::unique_ptr<QWidget> &each) {
        auto control = dynamic_cast<ManagementButton *>(each.release());
        nlohmann::json config;
        config[Mss::System::getJsonTextKey()] = control->getText();
        auto e = control->pos();
        config[Mss::System::getJsonPositionKey()] = {{ "x", control->pos().x() },
                                                     { "y", control->pos().y() }};
        config[Mss::System::getJsonSizeKey()] = {{ "x", control->size().width() },
                                                 { "y", control->size().height() }};
        fullConfig[type].push_back(config);
    });
    return fullConfig;
}

template<>
nlohmann::json Config::saveControls<QuickButton>(WorQWidgetPtrVec controls) noexcept {
    nlohmann::json fullConfig;
    constexpr std::string_view type = "Button";
    std::for_each(std::begin(controls), std::end(controls), [&fullConfig, &type](std::unique_ptr<QWidget> &each) {
        auto control = dynamic_cast<QuickButton *>(each.release());
        nlohmann::json config;
        config.at(Mss::System::getJsonTextKey()) = control->getText();
        config.at(Mss::System::getJsonPositionKey()) = {{ "x", control->pos().x() },
                                                        { "y", control->pos().y() }};
        config.at(Mss::System::getJsonSizeKey()) = {{ "x", control->size().width() },
                                                    { "y", control->size().height() }};
        fullConfig.at(type).push_back(config);
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
    WorQWidgetPtrVec qbControls;
    WorQWidgetPtrVec qtControls;

    std::for_each(std::begin(allControls), std::end(allControls), [&mbControls, &qbControls](QObject *each) {
        auto control = dynamic_cast<QWidget *>(each);
        if (dynamic_cast<const ManagementButton *>(each)) {
            std::printf("Management button was tracked.\n");
            mbControls.emplace_back(control);
        } else if (dynamic_cast<const QuickButton *>(each)) {
            std::printf("Button was tracked.\n");
            qbControls.emplace_back(control);
        }
    });

    nlohmann::json fullConfig;

//    nlohmann::json mbConfig = saveControls<ManagementButton>(std::move(mbControls));
//    nlohmann::json qbConfig = saveControls<QuickButton>(std::move(qbControls));
//
//    fullConfig.at(Mss::System::getJsonHeadKey()) = { mbConfig, qbConfig };

    std::string configPath = std::string(Mss::System::getResourcePath()) +
                             tabName + '/' +
                             std::string(Mss::System::getManagementScopeConfigName());
    return ::saveConfigFile(configPath, fullConfig);
}
