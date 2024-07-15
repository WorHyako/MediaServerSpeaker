#include "Files.hpp"

namespace {
    constexpr std::string_view resourceFolder = "Resources/";

    constexpr std::string_view quickButtonConfigFile = "QuickButtons.json";

    constexpr std::string_view quickTitleConfigFile = "QuickTitles.json";

    constexpr std::string_view managementButtonConfigFile = "ManagementButtons.json";
}

std::string_view Mss::System::getResourcePath() noexcept {
    return resourceFolder;
}

std::string_view Mss::System::getQuickButtonConfigName() noexcept {
    return quickButtonConfigFile;
}

std::string_view Mss::System::getQuickTitleConfigName() noexcept {
    return quickTitleConfigFile;
}

std::string_view Mss::System::getManagementButtonConfigName() noexcept {
    return managementButtonConfigFile;
}
