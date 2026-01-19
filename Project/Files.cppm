export module mss.project:Files;

import std;

namespace Mss::Gui::Scopes {
class QuickTitlesScope;

class QuickButtonScope;

class ManagementScope;
}

namespace {
constexpr std::string_view resource_folder{ "Resources/" };

constexpr std::string_view quick_button_scope_config_file{ "QuickScope.json" };

constexpr std::string_view quick_title_scope_config_file{ "TitlesScope.json" };

constexpr std::string_view management_scope_config_file{ "ManagementScope.json" };
}

export namespace Mss::System {
/**
 * @brief
 *
 * @return
 *
 * @author WorHyako
 */
[[nodiscard]]
constexpr std::string_view get_resource_path() noexcept {
    return ::resource_folder;
}

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
[[nodiscard]]
constexpr std::string_view get_config_name() noexcept {
    if constexpr (std::same_as<TScopeType, Gui::Scopes::QuickTitlesScope>) {
        return ::quick_title_scope_config_file;
    } else if constexpr (std::same_as<TScopeType, Gui::Scopes::QuickButtonScope>) {
        return ::quick_button_scope_config_file;
    } else if constexpr (std::same_as<TScopeType, Gui::Scopes::ManagementScope>) {
        return ::management_scope_config_file;
    } else {
        static_assert(true);
    }
}
}
