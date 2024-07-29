#include "WidgetControlStyle.hpp"

constexpr std::string_view widgetControlStyle = R"(
QWidget#WorControl {
    background-color: "#30949494";
    border-radius: 7px;
    border-width: 2px;
    border-color: "#939393";
}
)";

using namespace Mss::Gui;

std::string_view Style::getWidgetControlStyle() noexcept {
    return ::widgetControlStyle;
}
