#include "ControlsConfig.hpp"

#include "ControlCreator.hpp"
#include "Controls/ManagementButton.hpp"
#include "Controls/Button.hpp"

#include <string_view>

#include "WorLibrary/Json/JsonManager.hpp"

namespace {
    constexpr std::string_view resourceFolder = "Resources/";

    constexpr std::string_view quickButtonConfigFile = "QuickButtons.json";

    constexpr std::string_view quickTitleConfigFile = "QuickTitles.json";

    constexpr std::string_view managementButtonConfigFile = "ManagementButtons.json";

    constexpr std::string_view jsonHeadKey = "objects";

    constexpr std::string_view jsonTextKey = "text";

    constexpr std::string_view jsonCanMoveKey = "canMove";

    constexpr std::string_view jsonCanResizeKey = "canResize";

    constexpr std::string_view jsonPositionKey = "position";

    constexpr std::string_view jsonSizeKey = "size";

    std::string tabPath;
}

using namespace Mss::Gui;
using namespace Wor;

/**
 * Common methods
 */
namespace {
    /**
     * @brief
     *
     * @param configName
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    inline nlohmann::json loadConfigFile(const std::string &configName) {
        auto config = Json::tryToLoadFile(configName);

        if (config.empty() ||
            !config.contains(std::string(::jsonHeadKey)) ||
            !config[std::string(::jsonHeadKey)].is_array()) {
            return {};
        }
        return config;
    }
}

namespace {
    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    Config::WorQWidgetPtrVec loadMButtons() noexcept {
        using ManagementButtonCreator = Config::ControlCreator<Controls::ManagementButton>;

        std::string filePath(tabPath + '/' + std::string(::managementButtonConfigFile));

        const auto json = ::loadConfigFile(filePath);
        if (json.empty()) {
            return {};
        }
        const auto config = json[std::string(::jsonHeadKey)];

        Config::WorQWidgetPtrVec controls;
        controls.reserve(config.size());

        for (const auto &each : config) {
            auto button = ManagementButtonCreator::create();
            try {
                std::string text = each[::jsonTextKey];
                button->setText(text.c_str());
                bool canMove = each[::jsonCanMoveKey];
                button->setCanMove(canMove);
                bool canResize = each[::jsonCanResizeKey];
                button->setCanResize(canResize);
                int xPos = each[::jsonPositionKey]["x"];
                int yPos = each[::jsonPositionKey]["y"];
                button->move(xPos, yPos);
                int xSize = each[::jsonSizeKey]["x"];
                int ySize = each[::jsonSizeKey]["y"];
                button->resize(xSize, ySize);
            } catch (const std::exception &e) {
                std::printf("Bad config for control!\n File: %s\n",
                            filePath.c_str());
                std::printf("Error: %s\n Bad object dump: %s\n",
                            e.what(), std::string(each.dump()).c_str());
                continue;
            }
            controls.push_back(std::move(button));
        }
        return controls;
    }

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    Config::WorQWidgetPtrVec loadQButtons() noexcept {
        using QuickButtonCreator = Config::ControlCreator<Controls::Button>;

        std::string filePath(tabPath + '/' + std::string(::managementButtonConfigFile));

        const auto json = ::loadConfigFile(filePath);
        if (json.empty()) {
            return {};
        }
        const auto config = json[std::string(::jsonHeadKey)];

        Config::WorQWidgetPtrVec controls;
        controls.reserve(config.size());

        for (const auto &each : config) {
            auto button = QuickButtonCreator::create();
            try {
                std::string text = each[::jsonTextKey];
                button->setText(text.c_str());
            } catch (const std::exception &e) {
                std::printf("Bad config for control!\n File: %s\n",
                            filePath.c_str());
                std::printf("Error: %s\n Bad object dump: %s\n",
                            e.what(), std::string(each.dump()).c_str());
                continue;
            }
            controls.push_back(std::move(button));
        }
        return controls;
    }
}

/**
 * TODO: make precompile with all wor controls
 */
//extern template class Config::ControlCreator<Controls::ManagementButton>;

Config::WorQWidgetPtrVec Config::load(const std::string &tabName, ScopeType scope) noexcept {
    ::tabPath = std::string(::resourceFolder) + tabName;

    WorQWidgetPtrVec controls;

    if (static_cast<std::uint8_t>(scope) && static_cast<std::uint8_t>(ScopeType::ControlTab)) {
        auto &&mButtons = ::loadMButtons();

        controls.insert(controls.cend(),
                        std::make_move_iterator(mButtons.begin()),
                        std::make_move_iterator(mButtons.end()));
        mButtons.clear();
    }

    if (static_cast<std::uint8_t>(scope) && static_cast<std::uint8_t>(ScopeType::QuickButtons)) {
        auto &&qButtons = ::loadQButtons();

        controls.insert(controls.cend(),
                        std::make_move_iterator(qButtons.begin()),
                        std::make_move_iterator(qButtons.end()));
        qButtons.clear();
    }

    return controls;
}
