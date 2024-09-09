#pragma once

#include <string_view>

namespace Mss::Gui::Style {
	/**
	 * @brief	Returns style sheet for QTextEdit object.
	 *
	 * @return	Style sheet.
	 *
	 * @author	WorHyako
	 */
	constexpr std::string_view getTextEditStyle() noexcept {
		return R"(
QTextEdit {
    border: 2px solid #939393;
    background-color: "#A4A4A4";
    border-radius: 7px;
    color: "#343434";
}
)";
	}
}
