#pragma once

#include "Command/ICommand.hpp"

#include <memory>

namespace Mss::Gui::Components {
/**
 * @brief Object separates all operations with server command.
 *
 * Designed for inheritance to add command functionality to other classes.
 *
 * @usage
 * @code
 *     CommandComponent::sessionName("session name");
 *     CommandItem item(...);
 *     CommandComponent::command()->addItem(commandItem);
 *     CommandComponent::execute();
 * @endcode
 *
 * @author WorHyako
 *
 * @see BaseCommand
 */
class CommandComponent {
  public:
    /**
     * @brief Constructor.
     */
    CommandComponent() noexcept;

    /**
     * @brief Destructor.
     */
    virtual ~CommandComponent() noexcept = default;

    /**
     * @brief Tries to execute command with current session name.
     *
     * @return true Successful command execution.
     * @return false Failed command execution.
     */
    [[nodiscard]]
    bool execute() const noexcept;

  private:
    std::shared_ptr<Backend::Command::ICommand> command_;

    std::string session_name_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the command.
     *
     * @param command New command. Pointer will be converted to std::shared_ptr.
     */
    void command(Backend::Command::ICommand *command) noexcept;

    /**
     * @brief Returns the command.
     *
     * @return Command.
     */
    [[nodiscard]]
    std::shared_ptr<Backend::Command::ICommand> command() const noexcept;

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

#pragma endregion Accessors / Mutators
};
}
