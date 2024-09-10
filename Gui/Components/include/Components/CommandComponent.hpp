#pragma once

#include <memory>

#include "Command/ICommand.hpp"

namespace Mss::Gui::Components {
	/**
	 * @brief	Object separates all operations with server command.
	 *			<p>
	 *			Orients just for inheritance existing.
	 *
	 * @usage
	 * @code
	 *			CommandComponent::sessionName("session name");
	 *			CommandItem item(...);
	 *			CommandComponent::command()->addItem(commandItem);
	 *			CommandComponent::execute();
	 * @endcode
	 *
	 * @author	WorHyako
	 *
	 * @see		@code BaseCommand @endcode
	 */
	class CommandComponent {
	public:
		/**
		 * @brief	Ctor.
		 */
		CommandComponent() noexcept;

		/**
		 * @brief	Dtor.
		 */
		virtual ~CommandComponent() noexcept = default;

		/**
		 * @brief	Try to execute command with current session name
		 *
		 * @return	@code true @endcode		Successful command executing.
		 *			<p>
		 *			@code false @endcode	Fail in command executing.
		 */
		[[nodiscard]]
		bool execute() const noexcept;

	private:
		std::shared_ptr<Backend::Command::ICommand> _command;

		std::string _sessionName;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Command mutator.
		 *
		 * @param	command	New command. Pointer will be modify to std::shared_pat
		 */
		void command(Backend::Command::ICommand* command) noexcept;

		/**
		 * @brief	Command accessor.
		 *
		 * @return	Command,
		 */
		[[nodiscard]]
		std::shared_ptr<Backend::Command::ICommand> command() const noexcept;

		/**
		 * @brief	Session name mutator.
		 *
		 * @param	sessionName	New session name.
		 */
		void sessionName(std::string sessionName) noexcept;

		/**
		 * @brief	Session name accessor.
		 *
		 * @return	Session name.
		 */
		[[nodiscard]]
		std::string sessionName() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
