#include "Files.hpp"

namespace {
    constexpr std::string_view resourceFolder = "Resources/";

    constexpr std::string_view quickButtonConfigFile = "QuickScope.json";

    constexpr std::string_view quickTitleConfigFile = "TitlesScope.json";

    constexpr std::string_view managementButtonConfigFile = "ManagementScope.json";
}

std::string_view Mss::System::getResourcePath() noexcept {
    return resourceFolder;
}

std::string_view Mss::System::getQuickScopeConfigName() noexcept {
    return quickButtonConfigFile;
}

std::string_view Mss::System::getTitlesScopeConfigName() noexcept {
    return quickTitleConfigFile;
}

std::string_view Mss::System::getManagementScopeConfigName() noexcept {
    return managementButtonConfigFile;
}
