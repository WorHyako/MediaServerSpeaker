#pragma once

#include "Command/ICommand.hpp"

#include <memory>

namespace Mss::Backend::Midi {
	/**
	 * @brief	Object to control server messages.
	 *			<p>
	 *			Controls active/passive status of launchpad's midi button.
	 *			<p>
	 *			Store roads in road map object.
	 *
	 * @usage
	 * @code
	 *			ServerRoad road;
	 *			road.activeCommand(command1);
	 *			road.deactiveCommand(command2);
	 *			road.go();
	 * @endcode
	 *
	 * @author	WorHyako
	 */
	class ServerRoad final {
	public:
		using WorCommandPtr = std::shared_ptr<Command::ICommand>;

		/**
		 * @brief Ctor.
		 *
		 * @param sessionName Session name to send command.
		 */
		explicit ServerRoad(std::string sessionName = {}) noexcept;

		/**
		 * @brief	Sends out message to session's endpoint if it's possible.
		 *			<p>
		 *			Change active status via internal class field @code _isActive @endcode .
		 */
		void go() noexcept;

	private:
		/**
		 * @brief Command in midi button active state.
		 */
		WorCommandPtr _activeCommand;

		/**
		 * @brief Command in midi button passive state.
		 */
		WorCommandPtr _deactiveCommand;

		/**
		 * @brief Session name to send message.
		 */
		std::string _sessionName;

		/**
		 * @brief Midi button state.
		 */
		bool _isActive;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Session name mutator.
		 *
		 * @param	sessionName New session name.
		 */
		void sessionName(std::string sessionName) noexcept;

		/**
		 * @brief	Session name accessor.
		 *
		 * @return	Session name.
		 */
		[[nodiscard]]
		std::string sessionName() const noexcept;

		/**
		 * @brief	Active command mutator.
		 *
		 * @param	command New command.
		 */
		void activeCommand(WorCommandPtr command) noexcept;

		/**
		 * @brief	Passive command mutator.
		 *
		 * @param	command New command.
		 */
		void deactiveCommand(WorCommandPtr command) noexcept;

		/**
		 * @brief	Current command.
		 *
		 * @return	Command.
		 */
		[[nodiscard]]
		WorCommandPtr currentCommand() const noexcept;

#pragma endregion Accessors/Mutators

	};
}
