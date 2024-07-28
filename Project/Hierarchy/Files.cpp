#include "Files.hpp"

namespace {
    constexpr std::string_view resourceFolder = "Resources/";

    constexpr std::string_view quickButtonScopeConfigFile = "QuickScope.json";

    constexpr std::string_view quickTitleScopeConfigFile = "TitlesScope.json";

    constexpr std::string_view managementScopeConfigFile = "ManagementScope.json";
}

using namespace Mss;

namespace Mss::Gui::Scopes {
    class QuickTitlesScope;

    class QuickButtonScope;

    class ManagementScope;
}

std::string_view Mss::System::getResourcePath() noexcept {
    return resourceFolder;
}

template<>
std::string_view System::getConfigName<Mss::Gui::Scopes::QuickTitlesScope>() noexcept {
    return ::quickTitleScopeConfigFile;
}

template<>
std::string_view System::getConfigName<Mss::Gui::Scopes::QuickButtonScope>() noexcept {
    return ::quickButtonScopeConfigFile;
}

template<>
std::string_view System::getConfigName<Mss::Gui::Scopes::ManagementScope>() noexcept {
    return ::managementScopeConfigFile;
}
