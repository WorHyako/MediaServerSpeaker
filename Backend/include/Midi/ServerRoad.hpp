#pragma once

#include "Command/ICommand.hpp"

#include <memory>

namespace Mss::Backend::Midi {
/**
 * @brief Object to control server messages.
 *
 * Controls active/passive status of launchpad's midi button.
 * Store roads in road map object.
 *
 * @usage
 * @code
 *     ServerRoad road;
 *     road.activeCommand(command1);
 *     road.deactiveCommand(command2);
 *     road.go();
 * @endcode
 *
 * @author WorHyako
 */
class ServerRoad final {
  public:
    using WorCommandPtr = std::shared_ptr<Command::ICommand>;

    /**
     * @brief Constructor.
     *
     * @param session_name Session name to send command.
     */
    explicit ServerRoad(std::string session_name = {}) noexcept;

    /**
     * @brief Sends out message to session's endpoint if it's possible.
     *
     * Changes active status via internal class field.
     */
    void go() noexcept;

  private:
    /**
     * @brief Command in midi button active state.
     */
    WorCommandPtr active_command_;

    /**
     * @brief Command in midi button passive state.
     */
    WorCommandPtr deactive_command_;

    /**
     * @brief Session name to send message.
     */
    std::string session_name_;

    /**
     * @brief Midi button state.
     */
    bool is_active_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the session name.
     *
     * @param session_name New session name.
     */
    void set_session_name(std::string session_name) noexcept;

    /**
     * @brief Returns the session name.
     *
     * @return Session name.
     */
    [[nodiscard]]
    std::string get_session_name() const noexcept;

    /**
     * @brief Sets the active command.
     *
     * @param command New command.
     */
    void active_command(WorCommandPtr command) noexcept;

    /**
     * @brief Sets the passive command.
     *
     * @param command New command.
     */
    void deactive_command(WorCommandPtr command) noexcept;

    /**
     * @brief Returns the current command.
     *
     * @return Command.
     */
    [[nodiscard]]
    WorCommandPtr current_command() const noexcept;

#pragma endregion Accessors / Mutators
};
}
