#include "JsonContentKeys.hpp"

namespace {
    constexpr std::string_view jsonHeadKey = "objects";

    constexpr std::string_view jsonTextKey = "text";

    constexpr std::string_view jsonCommandKey = "command";

    constexpr std::string_view jsonPositionKey = "position";

    constexpr std::string_view jsonSizeKey = "size";

    constexpr std::string_view jsonManagementButtonKey = "Management Button";

    constexpr std::string_view jsonManagementTextableButtonKey = "Management Textable Button";

    constexpr std::string_view jsonQuickButtonKey = "Quick Button";

    constexpr std::string_view jsonQuickTitleKey = "Quick Title";
}

using namespace Mss;

namespace Mss::Gui::Controls {
    class ManagementButton;

    class ManagementTextableButton;

    class QuickTitle;

    class QuickButton;
}

std::string_view System::getJsonHeadKey() noexcept {
    return ::jsonHeadKey;
}

std::string_view System::getJsonTextKey() noexcept {
    return ::jsonTextKey;
}

std::string_view System::getJsonCommandKey() noexcept {
    return ::jsonCommandKey;
}

std::string_view System::getJsonPositionKey() noexcept {
    return ::jsonPositionKey;
}

std::string_view System::getJsonSizeKey() noexcept {
    return ::jsonSizeKey;
}

template<>
std::string_view System::getControlKey<Mss::Gui::Controls::ManagementButton>() noexcept {
    return ::jsonManagementButtonKey;
}

template<>
std::string_view System::getControlKey<Mss::Gui::Controls::ManagementTextableButton>() noexcept {
    return ::jsonManagementTextableButtonKey;
}

template<>
std::string_view System::getControlKey<Mss::Gui::Controls::QuickButton>() noexcept {
    return ::jsonQuickButtonKey;
}

template<>
std::string_view System::getControlKey<Mss::Gui::Controls::QuickTitle>() noexcept {
    return ::jsonQuickTitleKey;
}
