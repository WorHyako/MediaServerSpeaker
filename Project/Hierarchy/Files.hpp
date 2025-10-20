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
constexpr std::string_view get_resource_path() noexcept;

/**
 * @brief
 *
 * @tparam TScopeType
 *
 * @return
 *
 * @author WorHyako
 */
template <class TScopeType>
    requires std::same_as<TScopeType, Gui::Scopes::QuickTitlesScope>
             || std::same_as<TScopeType, Gui::Scopes::QuickButtonScope>
             || std::same_as<TScopeType, Gui::Scopes::ManagementScope>
[[nodiscard]]
constexpr std::string_view get_config_name() noexcept;
}
