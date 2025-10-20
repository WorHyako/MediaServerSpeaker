#include "JsonContentKeys.hpp"

namespace {
constexpr std::string_view json_head_key = "objects";

constexpr std::string_view json_text_key = "text";

constexpr std::string_view json_command_key = "command";

constexpr std::string_view json_position_key = "position";

constexpr std::string_view json_size_key = "size";

constexpr std::string_view json_session_name_key = "sessionName";

constexpr std::string_view json_midi_key_idx_key = "midiButtonId";

constexpr std::string_view json_management_button_key = "Management Button";

constexpr std::string_view json_management_textable_button_key = "Management Textable Button";

constexpr std::string_view json_quick_button_key = "Quick Button";

constexpr std::string_view json_quick_title_key = "Quick Title";
}

using namespace Mss;

namespace Mss::Gui::Controls {
class ManagementButton;

class ManagementTextableButton;

class QuickTitle;

class QuickButton;
}

constexpr std::string_view System::json_head_key() noexcept {
    return ::json_head_key;
}

constexpr std::string_view System::json_text_key() noexcept {
    return ::json_text_key;
}

constexpr std::string_view System::json_command_key() noexcept {
    return ::json_command_key;
}

constexpr std::string_view System::json_position_key() noexcept {
    return ::json_position_key;
}

constexpr std::string_view System::json_size_key() noexcept {
    return ::json_size_key;
}

constexpr std::string_view System::json_session_name_key() noexcept {
    return ::json_session_name_key;
}

constexpr std::string_view System::json_midi_button_id_key() noexcept {
    return ::json_midi_key_idx_key;
}

template <>
constexpr std::string_view System::json_control_key<Gui::Controls::ManagementButton>() noexcept {
    return ::json_management_button_key;
}

template <>
constexpr std::string_view System::json_control_key<Gui::Controls::ManagementTextableButton>() noexcept {
    return ::json_management_textable_button_key;
}

template <>
constexpr std::string_view System::json_control_key<Gui::Controls::QuickButton>() noexcept {
    return ::json_quick_button_key;
}

template <>
constexpr std::string_view System::json_control_key<Gui::Controls::QuickTitle>() noexcept {
    return ::json_quick_title_key;
}
