#include "TextEditStyle.hpp"

constexpr std::string_view textStyle = R"(
QTextEdit {
    border: 2px solid #939393;
    background-color: "#A4A4A4";
    border-radius: 7px;
    color: "#343434";
}
)";

using namespace Mss::Gui;

std::string_view Style::getTextEditStyle() noexcept {
    return ::textStyle;
}
