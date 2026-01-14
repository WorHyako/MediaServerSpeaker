export module mss.gui:style.WorStyle;
import :style.ButtonStyle;
import :style.LineEditStyle;
import :style.TextEditStyle;
import :style.WidgetControlStyle;

import std;

export namespace Mss::Gui::Style {
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
    constexpr std::string get_wor_style() noexcept {
        return std::string() + get_widget_control_style().data() + get_button_style().data() +
               get_text_edit_style().data() + get_line_edit_style().data();
    }
}
