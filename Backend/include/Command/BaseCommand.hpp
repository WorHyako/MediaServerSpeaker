#pragma once

#include "ICommand.hpp"

namespace Mss::Backend::Command {

/**
 * @brief Represents basic command class.
 *
 * Stores command via CommandItem list and data about session to send command.
 *
 * @usage
 * @code
 *     auto command = CommandBuilder<BaseCommand>::build();
 *     command.markTag("action");
 *
 *     CommandItem item{"key", "value"};
 *     command.addItem(item);
 *
 *     std::string commandStr = command.str();
 * @endcode
 *
 * @see CommandBuilder
 * @see CommandItem
 *
 * @author WorHyako
 */
class BaseCommand : public ICommand {
  public:
    /**
     * @brief Destructor.
     */
    ~BaseCommand() override = default;

    /**
     * @brief Adds selected item to command.
     *
     * @param item Item to add.
     */
    void add_item(CommandItem item) noexcept override;

    /**
     * @brief Adds selected items to command.
     *
     * @param items Items to add.
     */
    void add_items(std::vector<CommandItem> items) noexcept override;

    /**
     * @brief Removes item by key from command.
     *
     * @param item Item to remove.
     */
    void remove_item(CommandItem item) noexcept override;

    /**
     * @brief Removes item by key from command.
     *
     * @param key Key of item to remove.
     */
    void remove_item(std::string key) noexcept override;

    /**
     * @brief Removes item by index from command.
     *
     * @param idx Index of item to remove.
     */
    void remove_item(std::uint16_t idx) noexcept override;

    /**
     * @brief Removes last item from command.
     */
    void remove_item() noexcept override;

    /**
     * @brief Removes all items from command.
     */
    void clean() noexcept override;

    /**
     * @brief Executes command.
     *
     * Searches session in current server and tries to send command to endpoint.
     *
     * @param session_name Session name to send command.
     *
     * @return true Success executing.
     * @return false Fail in executing.
     */
    [[nodiscard]]
    bool execute(std::string session_name) const noexcept override;

    /**
     * @brief Changes item by key.
     *
     * Nothing will happen, if item doesn't exist.
     *
     * @param item Item to change.
     */
    void change_item(CommandItem item) noexcept override;

    /**
     * @brief Changes item by index.
     *
     * Nothing will happen, if index out of range.
     *
     * @param idx Index of item to change.
     * @param item New item.
     */
    void change_item(std::uint16_t idx, CommandItem item) noexcept override;

    /**
     * @brief Returns index of item with selected key.
     *
     * @param key Item's key to search.
     *
     * @return Index of item, or -1 if there is no item with selected key.
     */
    [[nodiscard]]
    std::int16_t indexOf(std::string key) const noexcept override;

  protected:
    /**
     * @brief Command tag. It's root of xml packet.
     */
    std::string tag_;

    /**
     * @brief Separated command parts via CommandItem.
     *
     * @see CommandItem
     */
    std::vector<CommandItem> items_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Returns command tag.
     *
     * @return Command tag.
     */
    [[nodiscard]]
    std::string get_tag() const noexcept override;

    /**
     * @brief Marks command with selected tag.
     *
     * @param tag Command tag.
     */
    void set_tag(std::string tag) noexcept override;

    /**
     * @brief Returns vector of command items.
     *
     * @return Command items.
     */
    [[nodiscard]]
    std::vector<CommandItem> items() const noexcept override;

    /**
     * @brief Tries to parse selected string to command items and fill it.
     *
     * @param command_str Command via string.
     */
    void set(const std::string &command_str) noexcept override;

    /**
     * @brief Converts command to string.
     *
     * @return Command via string representation.
     */
    [[nodiscard]]
    std::string str() const noexcept override;

#pragma endregion Accessors / Mutators
};
}
