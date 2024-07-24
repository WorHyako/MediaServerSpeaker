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
}

using namespace Mss;

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

std::string_view System::getManagementButtonKey() noexcept {
    return ::jsonManagementButtonKey;
}

std::string_view System::getManagementTextableButtonKey() noexcept {
    return ::jsonManagementTextableButtonKey;
}

std::string_view System::getQuickButtonKey() noexcept {
    return ::jsonQuickButtonKey;
}
