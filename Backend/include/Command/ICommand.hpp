#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "CommandItem.hpp"

namespace Mss::Backend::Command {

	/**
	 * @brief	Represents interface for command classes.
	 *
	 * @author WorHyako
	 */
	class ICommand {
	public:
		/**
		 * @brief Dtor.
		 */
		virtual ~ICommand() = default;

		/**
		 * @brief	Executes command.
		 *			Searches session in current server and tries to send command to endpoint.
		 *
		 * @param	sessionName	Session name to send command.
		 *
		 * @return	@code true @endcode		Success executing
		 *			<p>
		 *			@code false @endcode	Fail in executing
		 */
		[[nodiscard]]
		virtual bool execute(std::string sessionName) const noexcept = 0;

		/**
		 * @brief   Removes all items from command.
		 */
		virtual void clean() noexcept = 0;

		/**
		 * @brief   Add selected item to command.
		 *
		 * @param   item	Item to add
		 */
		virtual void addItem(CommandItem item) noexcept = 0;

		/**
		 * @brief   Add selected items to command.
		 *
		 * @param   items	Items to add.
		 */
		virtual void addItems(std::vector<CommandItem> items) noexcept = 0;

		/**
		 * @brief   Removes item by key from command
		 *
		 * @param   item	Item to remove
		 */
		virtual void removeItem(CommandItem item) noexcept = 0;

		/**
		 * @brief   Removes item by key from command.
		 *
		 * @param   key		Key of item to remove
		 */
		virtual void removeItem(std::string key) noexcept = 0;

		/**
		 * @brief   Removes item by index from command.
		 *
		 * @param   idx		Index of item to remove.
		 */
		virtual void removeItem(std::uint16_t idx) noexcept = 0;

		/**
		 * @brief   Removes last item from command.
		 */
		virtual void removeItem() noexcept = 0;

		/**
		 * @brief   Changes item by key.
		 *          <p>
		 *          Nothing will happen, if item doesn't exist.
		 *
		 * @param   item	Item to change
		 */
		virtual void changeItem(CommandItem item) noexcept = 0;

		/**
		 * @brief   Changes item by index.
		 *          <p>
		 *          Nothing will happen, if index out of range.
		 *
		 * @param   idx     Index of item to change
		 *
		 * @param   item    New item
		 */
		virtual void changeItem(std::uint16_t idx, CommandItem item) noexcept = 0;

		/**
		 * @brief   Returns index of item with selected key.
		 *
		 * @param   key		Item's key to search.
		 *
		 * @return  Index of item
		 *          <p/>
		 *          @code -1 @endcode If there is no item with selected key
		 */
		[[nodiscard]]
		virtual std::int16_t indexOf(std::string key) const noexcept = 0;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief   Returns vector of command items.
		 *
		 * @return  Command items
		 */
		[[nodiscard]]
		virtual std::vector<CommandItem> items() const noexcept = 0;

		/**
		 * @brief   Convert command to string.
		 *
		 * @return  Command via string representation
		 */
		[[nodiscard]]
		virtual std::string str() const noexcept = 0;

		/**
		 * @brief   Marks command with selected tag.
		 *
		 * @param   tag		Command tag
		 */
		virtual void tag(std::string tag) noexcept = 0;

		/**
		 * @brief   Returns command tag.
		 *
		 * @return  Command tag
		 */
		[[nodiscard]]
		virtual std::string tag() const noexcept = 0;

		/**
		 * @brief   Try to parse selected string to command items and fill it.
		 *
		 * @param   commandStr	Command via string
		 */
		virtual void set(const std::string &commandStr) noexcept = 0;

#pragma endregion Accessors/Mutators
	};
}
