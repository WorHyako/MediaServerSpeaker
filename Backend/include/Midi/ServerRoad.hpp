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
		/**
		 * @brief
		 */
		void go() noexcept;

	private:
		std::shared_ptr<Command::ICommand> _activeCommand;

		std::shared_ptr<Command::ICommand> _deactiveCommand;
	};
}
