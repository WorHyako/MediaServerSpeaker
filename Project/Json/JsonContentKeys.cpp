#include "JsonContentKeys.hpp"

namespace {
    constexpr std::string_view jsonHeadKey = "objects";

    constexpr std::string_view jsonTextKey = "text";

    constexpr std::string_view jsonCanMoveKey = "canMove";

    constexpr std::string_view jsonCanResizeKey = "canResize";

    constexpr std::string_view jsonPositionKey = "position";

    constexpr std::string_view jsonSizeKey = "size";
}

using namespace Mss;

std::string_view System::getJsonHeadKey() noexcept {
    return jsonHeadKey;
}

std::string_view System::getJsonTextKey() noexcept {
    return jsonTextKey;
}

std::string_view System::getJsonCanMoveKey() noexcept {
    return jsonCanMoveKey;
}

std::string_view System::getJsonCanResizeKey() noexcept {
    return jsonCanResizeKey;
}

std::string_view System::getJsonPositionKey() noexcept {
    return jsonPositionKey;
}

std::string_view System::getJsonSizeKey() noexcept {
    return jsonSizeKey;
}
