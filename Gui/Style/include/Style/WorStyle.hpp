#pragma once

#include "ButtonStyle.hpp"
#include "LineEditStyle.hpp"
#include "TextEditStyle.hpp"
#include "WidgetControlStyle.hpp"

#include <string>

namespace Mss::Gui::Style {
/**
 * @brief Returns all Wor styles for controls
 *
 * @usage
 * @code
 *     window.setStyleSheet(Style::getWorStyle().c_str());
 * @endcode
 *
 * @return Styles sheet.
 *
 * @author WorHyako
 */
[[nodiscard]]
static constexpr std::string get_wor_style() noexcept {
    return std::string() + get_widget_control_style().data() + get_button_style().data() +
           get_text_edit_style().data() + get_line_edit_style().data();
}
}
