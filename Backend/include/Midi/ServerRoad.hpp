#pragma once

#include "Command/ICommand.hpp"

#include <memory>

namespace Mss::Backend::Midi {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ServerRoad final {
	public:
		using WorCommandPtr = std::shared_ptr<Command::ICommand>;

		/**
		 * @brief Ctor.
		 *
		 * @param sessionName
		 */
		explicit ServerRoad(std::string sessionName = {}) noexcept;

		/**
		 * @brief
		 */
		void go() noexcept;

	private:
		WorCommandPtr _activeCommand;

		WorCommandPtr _deactiveCommand;

		std::string _sessionName;

		bool _isActive;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param sessionName
		 */
		void sessionName(std::string sessionName) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::string sessionName() const noexcept;

		/**
		 * @brief
		 *
		 * @param command
		 */
		void activeCommand(WorCommandPtr command) noexcept;

		/**
		 * @brief
		 *
		 * @param command
		 */
		void deactiveCommand(WorCommandPtr command) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		WorCommandPtr currentCommand() const noexcept;

#pragma endregion Accessors/Mutators

	};
}
