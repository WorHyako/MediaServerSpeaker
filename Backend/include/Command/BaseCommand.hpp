#pragma once

#include "ICommand.hpp"

namespace Mss::Backend::Command {

	/**
	 * @brief
	 *
	 * @usage
	 * @code
	 *          auto command = CommandBuilder<BaseCommand>::build();
	 *          command.markTag("action");
	 *
	 *          CommandItem item{"key", "value"};
	 *          command.addItem(item);
	 *
	 *          std::string commandStr = command.str();
	 * @endcode
	 *
	 * @see     <code>CommandBuilder</code>
	 * @see     <code>CommandItem</code>
	 *
	 * @author  WorHyako
	 */
	class BaseCommand
			: public ICommand {
	public:
		/**
		 * @brief Dtor.
		 */
		~BaseCommand() override = default;

		/**
		 * @brief   Add selected item to command.
		 *
		 * @param   item Item to add
		 */
		void addItem(CommandItem item) noexcept override;

		/**
		 * @brief   Add selected items to command.
		 *
		 * @param   items Items to add.
		 */
		void addItems(std::vector<CommandItem> items) noexcept override;

		/**
		 * @brief   Removes item by key from command
		 *
		 * @param   item Item to remove
		 */
		void removeItem(CommandItem item) noexcept override;

		/**
		 * @brief   Removes item by key from command.
		 *
		 * @param   key Key of item to remove
		 */
		void removeItem(std::string key) noexcept override;

		/**
		 * @brief   Removes item by index from command.
		 *
		 * @param   idx Index of item to remove.
		 */
		void removeItem(std::uint16_t idx) noexcept override;

		/**
		 * @brief   Removes last item from command.
		 */
		void removeItem() noexcept override;

		/**
		 * @brief   Removes all items from command.
		 */
		void clean() noexcept override;

		/**
		 * @brief
		 *
		 * @param sessionName
		 *
		 * @return
		 */
		[[nodiscard]]
		bool execute(std::string sessionName) const noexcept override;

		/**
		 * @brief   Changes item by key.
		 *          <p/>
		 *          Nothing will happened, if item doesn't exist.
		 *
		 * @param   item Item to change
		 */
		void changeItem(CommandItem item) noexcept override;

		/**
		 * @brief   Changes item by index.
		 *          <p/>
		 *          Nothing will happened, if index out of range.
		 *
		 * @param   idx     Index of item to change
		 *
		 * @param   item    New item
		 */
		void changeItem(std::uint16_t idx, CommandItem item) noexcept override;

		/**
		 * @brief   Returns index of item with selected key.
		 *
		 * @param   key Item's key to search.
		 *
		 * @return  Index of item
		 *          <p/>
		 *          <code>-1</code> if there is no item with selected key
		 */
		[[nodiscard]]
		std::int16_t indexOf(std::string key) const noexcept override;

	protected:
		std::string _tag;

		std::vector<CommandItem> _items;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief   Returns command tag.
		 *
		 * @return  Command tag
		 */
		[[nodiscard]]
		std::string tag() const noexcept override;

		/**
		 * @brief   Marks command with selected tag.
		 *
		 * @param   tag Command tag
		 */
		void tag(std::string tag) noexcept override;

		/**
		 * @brief   Returns vector of command items.
		 *
		 * @return  Command items
		 */
		[[nodiscard]]
		std::vector<CommandItem> items() const noexcept override;

		/**
		 * @brief   Try to parse selected string to command items and fill it.
		 *
		 * @param   commandStr Command via string
		 */
		void set(const std::string &commandStr) noexcept override;

		/**
		 * @brief   Convert command to string.
		 *
		 * @return  Command via string representation
		 */
		[[nodiscard]]
		std::string str() const noexcept override;

#pragma endregion Accessors/Mutators
	};
}
