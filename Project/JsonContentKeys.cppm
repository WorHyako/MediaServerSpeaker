export module mss.project:JsonContentKeys;

import std;

namespace Mss::Gui::Controls {
class ManagementButton;

class ManagementTextableButton;

class QuickTitle;

class QuickButton;
}

namespace {
constexpr std::string_view json_head_key{ "objects" };

constexpr std::string_view json_text_key{ "text" };

constexpr std::string_view json_command_key{ "command" };

constexpr std::string_view json_position_key{ "position" };

constexpr std::string_view json_size_key{ "size" };

constexpr std::string_view json_session_name_key{ "sessionName" };

constexpr std::string_view json_midi_key_idx_key{ "midiButtonId" };

constexpr std::string_view json_management_button_key{ "Management Button" };

constexpr std::string_view json_management_textable_button_key{ "Management Textable Button" };

constexpr std::string_view json_quick_button_key{ "Quick Button" };

constexpr std::string_view json_quick_title_key{ "Quick Title" };
}

export namespace Mss::System {

/**
 * @brief
 *
 * @tparam TControlType
 *
 * @return
 */
template <class TControlType>
[[nodiscard]]
constexpr std::string_view json_control_key() noexcept {
    if constexpr (std::is_same_v<TControlType, Gui::Controls::ManagementButton>) {
        return ::json_management_button_key;
    } else if constexpr (std::is_same_v<TControlType, Gui::Controls::ManagementTextableButton>) {
        return ::json_management_textable_button_key;
    } else if constexpr (std::is_same_v<TControlType, Gui::Controls::QuickButton>) {
        return ::json_quick_button_key;
    } else if constexpr (std::is_same_v<TControlType, Gui::Controls::QuickTitle>) {
        return ::json_quick_title_key;
    } else {
        static_assert(true);
    }
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_head_key() noexcept {
    return ::json_head_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_text_key() noexcept {
    return ::json_text_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_midi_button_id_key() noexcept {
    return ::json_midi_key_idx_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_command_key() noexcept {
    return ::json_command_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_position_key() noexcept {
    return ::json_position_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_size_key() noexcept {
    return ::json_size_key;
}

/**
 * @brief
 *
 * @return
 *
 * @author WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_session_name_key() noexcept {
    return ::json_session_name_key;
}
}
