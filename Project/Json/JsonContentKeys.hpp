#pragma once

#include <string_view>

namespace Mss::System {
/**
 * @brief
 *
 * @tparam TControlType
 *
 * @return
 */
template <class TControlType>
[[nodiscard]]
constexpr std::string_view json_control_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_head_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_text_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_midi_button_id_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_command_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_position_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author  WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_size_key() noexcept;

/**
 * @brief
 *
 * @return
 *
 * @author WorHyako
 */
[[nodiscard]]
constexpr std::string_view json_session_name_key() noexcept;
}
