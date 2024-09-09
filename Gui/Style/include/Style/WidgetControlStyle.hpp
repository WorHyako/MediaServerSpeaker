#pragma once

#include <string_view>

namespace Mss::Gui::Style {
	/**
	 * @brief	Returns style sheet fpr QWidget object named "WorControl".
	 *			<p>
	 *			It will paint background with rounded corners.
	 *
	 * @return	Style sheet.
	 *
	 * @author	WorHyako
	 */
	constexpr std::string_view getWidgetControlStyle() noexcept {
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
