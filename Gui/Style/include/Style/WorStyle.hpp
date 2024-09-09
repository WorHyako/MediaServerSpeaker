#pragma once

#include "WidgetControlStyle.hpp"
#include "TextEditStyle.hpp"
#include "LineEditStyle.hpp"
#include "ButtonStyle.hpp"

#include <string>

namespace Mss::Gui::Style {
	/**
	 * @brief	Returns all Wor styles for controls
	 *
	 * @usage
	 * @code
	 *			window.setStyleSheet(Style::getWorStyle().c_str());
	 * @endcode
	 *
	 * @return	Styles sheet.
	 *
	 * @author	WorHyako
	 */
	[[nodiscard]]
	static std::string getWorStyle() noexcept {
		return std::string()
				+ getWidgetControlStyle().data()
				+ getButtonStyle().data()
				+ getTextEditStyle().data()
				+ getLineEditStyle().data();
	}
}
