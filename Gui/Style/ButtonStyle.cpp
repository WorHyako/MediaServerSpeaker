#include "ButtonStyle.hpp"

constexpr std::string_view managementButtonStyle = R"(
QPushButton {
    border: 2px solid #939393;
    border-radius: 7px;
    background-color: "#C4C4C4";
    color: "#343434";
}

QPushButton:hover {
    border: 3px solid #939393;
    border-radius: 7px;
    background-color: "#F4F4F4";
    color: "#343434";
}
)";

using namespace Mss::Gui;

std::string_view Style::getButtonStyle() noexcept {
    return ::managementButtonStyle;
}
