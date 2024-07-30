#pragma once

#include "WidgetControlStyle.hpp"
#include "TextEditStyle.hpp"
#include "ButtonStyle.hpp"

#include <string>

namespace Mss::Gui::Style {

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    static std::string getWorStyle() noexcept {
        return std::string()
               + Style::getWidgetControlStyle().data()
               + Style::getButtonStyle().data()
               + Style::getTextEditStyle().data();
    }
}
