#pragma once

#include <string_view>

namespace Mss::Gui::Style {
	/**
	 * @brief	Returns style sheet for QLineEdit object.
	 *
	 * @return	Style sheet.
	 *
	 * @author	WorHyako
	 */
	constexpr std::string_view getLineEditStyle() noexcept {
		return R"(
QLineEdit {
    border: 2px solid #939393;
    background-color: "#A4A4A4";
    border-radius: 7px;
    color: "#343434";
}
)";
	}
}
