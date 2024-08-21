#pragma once

#include <string_view>

namespace Mss::Gui::Scopes {
	class QuickTitlesScope;

	class QuickButtonScope;

	class ManagementScope;
}

namespace Mss::System {
	/**
	 * @brief
	 *
	 * @return
	 *
	 * @author WorHyako
	 */
	[[nodiscard]]
	std::string_view getResourcePath() noexcept;

	/**
	 * @brief
	 *
	 * @tparam TScopeType
	 *
	 * @return
	 */
	template <class TScopeType>
	[[nodiscard]]
	std::string_view getConfigName() noexcept;
}
