#pragma once

#include <string>

#include <nlohmann/json.hpp>

class QWidget;

namespace Mss::Gui::Config {

    /**
     * @brief
     *
     * @author WorHyako
     */
    enum class ScopeType
            : std::uint8_t {
        /**
         *
         */
        ControlTab = 0b1,
        /**
         *
         */
        QuickButtons = 0b10,
        /**
         *
         */
        QuickTitles = 0b100,
        /**
         *
         */
        All = 0b111,
    };

    using WorQWidgetPtr = std::unique_ptr<QWidget>;
    using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

    /**
     * @brief
     *
     * @param tabName
     *
     * @return
     *
     * @author
     */
    [[nodiscard]]
    WorQWidgetPtrVec load(const std::string &tabName, ScopeType scope = ScopeType::All) noexcept;
}
