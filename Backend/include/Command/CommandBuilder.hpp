#pragma once

#include <vector>
#include <algorithm>

#include "CommandItem.hpp"

namespace Mss::Backend::Command {

	/**
	 * @brief	Object to create commands and log process.
	 *
	 * @usage
	 * @code
	 *			CommandBuilder<BaseCommand>::build();
	 * @endcode
	 *
	 * @tparam	TCommandType	Command class type
	 *
	 * @author	WorHyako
	 */
	template <class TCommandType>
	class CommandBuilder final {
	public:
		/**
		 * @brief Ctor.
		 */
		CommandBuilder() noexcept = delete;

		/**
		 * @brief	Creates command from selected CommandItems.
		 *
		 * @param	items	List of CommandItems to create command.
		 *
		 * @return	Unique pointer of created command.
		 *
		 * @see		@code CommandItem @endcode
		 */
		[[nodiscard]]
		static std::unique_ptr<TCommandType> build(std::vector<CommandItem> items = {}) noexcept;

		/**
		 * @warning Not ready yet.
		 *
		 * @brief
		 */
		[[deprecated]]
		static void log() noexcept;
	};

	template <class TCommandType>
	std::unique_ptr<TCommandType> CommandBuilder<TCommandType>::build(std::vector<CommandItem> items) noexcept {
		std::unique_ptr<TCommandType> command(new TCommandType);
		std::ranges::for_each(items,
							  [&command](const auto &each) {
								  command->addItem(std::move(each));
							  });
		return command;
	}

	template <class CommandType>
	void CommandBuilder<CommandType>::log() noexcept {
	}
}
