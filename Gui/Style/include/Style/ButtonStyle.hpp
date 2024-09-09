#pragma once

#include <string_view>

namespace Mss::Gui::Style {
	/**
	 * @brief	Returns style sheet for QPushButton object.
	 *
	 * @return	Style sheet.
	 *
	 * @author	WorHyako
	 */
	constexpr std::string_view getButtonStyle() noexcept {
		return R"(
QPushButton {
    border: 2px solid #939393;
    border-radius: 7px;
    background-color: "#C4C4C4";
    color: "#343434";
}

QPushButton:hover {
    border: 1px solid #939393;
    background-color: "#D4D4D4";
}

QPushButton:pressed {
    background-color: "#A4A4A4";
}
)";
	}
}
