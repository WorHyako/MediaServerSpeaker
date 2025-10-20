#include "Files.hpp"

namespace {
constexpr std::string_view resource_folder = "Resources/";

constexpr std::string_view quick_button_scope_config_file = "QuickScope.json";

constexpr std::string_view quick_title_scope_config_file = "TitlesScope.json";

constexpr std::string_view management_scope_config_file = "ManagementScope.json";
}

using namespace Mss;

namespace Mss::Gui::Scopes {
class QuickTitlesScope;

class QuickButtonScope;

class ManagementScope;
}

constexpr std::string_view System::get_resource_path() noexcept {
    return resource_folder;
}

template <>
constexpr std::string_view System::get_config_name<Gui::Scopes::QuickTitlesScope>() noexcept {
    return ::quick_title_scope_config_file;
}

template <>
constexpr std::string_view System::get_config_name<Gui::Scopes::QuickButtonScope>() noexcept {
    return ::quick_button_scope_config_file;
}

template <>
constexpr std::string_view System::get_config_name<Gui::Scopes::ManagementScope>() noexcept {
    return ::management_scope_config_file;
}
