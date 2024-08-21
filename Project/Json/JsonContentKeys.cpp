#include "JsonContentKeys.hpp"

namespace {
	constexpr std::string_view jsonHeadKey = "objects";

	constexpr std::string_view jsonTextKey = "text";

	constexpr std::string_view jsonCommandKey = "command";

	constexpr std::string_view jsonPositionKey = "position";

	constexpr std::string_view jsonSizeKey = "size";

	constexpr std::string_view jsonSessionNameKey = "sessionName";

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

std::string_view System::jsonHeadKey() noexcept {
	return ::jsonHeadKey;
}

std::string_view System::jsonTextKey() noexcept {
	return ::jsonTextKey;
}

std::string_view System::jsonCommandKey() noexcept {
	return ::jsonCommandKey;
}

std::string_view System::jsonPositionKey() noexcept {
	return ::jsonPositionKey;
}

std::string_view System::jsonSizeKey() noexcept {
	return ::jsonSizeKey;
}

std::string_view System::jsonSessionNameKey() noexcept {
	return ::jsonSessionNameKey;
}

template <>
std::string_view System::jsonControlKey<Mss::Gui::Controls::ManagementButton>() noexcept {
	return ::jsonManagementButtonKey;
}

template <>
std::string_view System::jsonControlKey<Mss::Gui::Controls::ManagementTextableButton>() noexcept {
	return ::jsonManagementTextableButtonKey;
}

template <>
std::string_view System::jsonControlKey<Mss::Gui::Controls::QuickButton>() noexcept {
	return ::jsonQuickButtonKey;
}

template <>
std::string_view System::jsonControlKey<Mss::Gui::Controls::QuickTitle>() noexcept {
	return ::jsonQuickTitleKey;
}
