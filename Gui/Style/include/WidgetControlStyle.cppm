export module mss.gui:style.WidgetControlStyle;

import std;

export namespace Mss::Gui::Style {
/**
 * @brief Returns style sheet fpr QWidget object named "WorControl".
 *
 * It will paint background with rounded corners.
 *
 * @return Style sheet.
 *
 * @author WorHyako
 */
constexpr std::string_view get_widget_control_style() noexcept {
    return R"(
QWidget#WorControl {
    background-color: "#30949494";
    border-radius: 7px;
    border-width: 2px;
    border-color: "#939393";
}
)";
}
}
