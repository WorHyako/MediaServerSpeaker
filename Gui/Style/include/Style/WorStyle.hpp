#pragma once

#include "WidgetControlStyle.hpp"
#include "TextEditStyle.hpp"
#include "LineEditStyle.hpp"
#include "ButtonStyle.hpp"

#include <string>

namespace Mss::Gui::Style {
	/**
	 * @brief
	 *
	 * @return
	 *
	 * @author WorHyako
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
