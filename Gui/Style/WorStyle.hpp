#pragma once

#include "Style/WidgetControlStyle.hpp"
#include "Style/TextEditStyle.hpp"
#include "Style/ButtonStyle.hpp"

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
