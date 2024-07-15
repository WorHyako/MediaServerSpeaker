#include "Config.hpp"

#include "Scopes/ManagementScope.hpp"
#include "Scopes/QuickButtonScope.hpp"

#include "Controls/ManagementButton.hpp"

#include "ControlCreator.hpp"
#include "Hierarchy/Files.hpp"
#include "Json/JsonContentKeys.hpp"

#include "WorLibrary/Json/JsonManager.hpp"

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

template<>
template<class TControlType = ManagementButton>
Controls::WorQWidgetPtrVec Config<Scopes::ManagementScope>::loadControls(const nlohmann::json &json) noexcept {
    using ControlCreator = ControlCreator<TControlType>;

    WorQWidgetPtrVec controls;
    const auto config = json[std::string(System::getJsonHeadKey())];
    controls.reserve(config.size());
    std::for_each(std::begin(config), std::end(config), [&controls](auto &each) {
        auto button = ControlCreator::create();
        try {
            std::string text = each[System::getJsonTextKey()];
            button->setText(text);
            bool canMove = each[System::getJsonCanMoveKey()];
            button->setCanMove(canMove);
            bool canResize = each[System::getJsonCanResizeKey()];
            button->setCanResize(canResize);
            int xPos = each[System::getJsonPositionKey()]["x"];
            int yPos = each[System::getJsonPositionKey()]["y"];
            button->move(xPos, yPos);
            int xSize = each[System::getJsonSizeKey()]["x"];
            int ySize = each[System::getJsonSizeKey()]["y"];
            button->resize(xSize, ySize);
        } catch (const std::exception &e) {
            std::printf("Error: %s\n Bad object dump: %s\n",
                        e.what(), std::string(each.dump()).c_str());
            return;
        }
        controls.push_back(std::move(button));
    });

    return controls;
}

template<>
template<>
WorQWidgetPtrVec Config<Scopes::ManagementScope>::loadControls<Button>(const nlohmann::json &json) noexcept {
    using QuickButtonCreator = ControlCreator<Controls::Button>;
    return {};
}

template<>
WorQWidgetPtrVec Config<Scopes::ManagementScope>::load(const std::string &tabName) noexcept {
    std::string tabPath = std::string(System::getResourcePath()) + tabName + '/';
    WorQWidgetPtrVec controls;

    std::string mbConfigPath(tabPath + std::string(System::getManagementButtonConfigName()));
    std::string qbConfigPath(tabPath + std::string(System::getQuickButtonConfigName()));
    std::string qtConfigPath(tabPath + std::string(System::getQuickTitleConfigName()));

    const auto mbJson = loadConfigFile(mbConfigPath);
    const auto qbJson = loadConfigFile(qbConfigPath);
    const auto qtJson = loadConfigFile(qtConfigPath);

    if (mbJson.empty() || qbJson.empty() || qtJson.empty()) {
        return {};
    }

    auto mbControls = Config::loadControls<Controls::ManagementButton>(mbJson);
    auto qbControls = Config::loadControls<Controls::Button>(mbJson);

    controls.reserve(mbControls.size() + qbControls.size());
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mbControls)), std::make_move_iterator(std::end(mbControls)));
//    std::move(std::begin(mbControls), std::end(mbControls), std::begin(controls));
//    std::move(std::begin(qbControls), std::end(qbControls), std::end(controls));

    qbControls.clear();
    mbControls.clear();
    return controls;
}

template<>
WorQWidgetPtrVec Config<Scopes::QuickButtonScope>::load(const std::string &tabName) noexcept {
    return {};
}

template<class TScopeType>
inline nlohmann::json Config<TScopeType>::loadConfigFile(const std::string &configName) {
    auto config = Wor::Json::tryToLoadFile(configName);

    const auto headKey = std::string(System::getJsonHeadKey());
    if (config.empty() ||
        !config.contains(headKey) ||
        !config[headKey].is_array()) {
        return {};
    }
    return config;
}
