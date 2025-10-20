#pragma once

#include "CommandItem.hpp"

#include <string>
#include <vector>

namespace Mss::Backend::Command {

/**
 * @brief Represents interface for command classes.
 *
 * @author WorHyako
 */
class ICommand {
  public:
    /**
     * @brief Destructor.
     */
    virtual ~ICommand() = default;

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
    virtual bool execute(std::string session_name) const noexcept = 0;

    /**
     * @brief Removes all items from command.
     */
    virtual void clean() noexcept = 0;

    /**
     * @brief Adds selected item to command.
     *
     * @param item Item to add.
     */
    virtual void add_item(CommandItem item) noexcept = 0;

    /**
     * @brief Adds selected items to command.
     *
     * @param items Items to add.
     */
    virtual void add_items(std::vector<CommandItem> items) noexcept = 0;

    /**
     * @brief Removes item by key from command.
     *
     * @param item Item to remove.
     */
    virtual void remove_item(CommandItem item) noexcept = 0;

    /**
     * @brief Removes item by key from command.
     *
     * @param key Key of item to remove.
     */
    virtual void remove_item(std::string key) noexcept = 0;

    /**
     * @brief Removes item by index from command.
     *
     * @param idx Index of item to remove.
     */
    virtual void remove_item(std::uint16_t idx) noexcept = 0;

    /**
     * @brief Removes last item from command.
     */
    virtual void remove_item() noexcept = 0;

    /**
     * @brief Changes item by key.
     *
     * Nothing will happen, if item doesn't exist.
     *
     * @param item Item to change.
     */
    virtual void change_item(CommandItem item) noexcept = 0;

    /**
     * @brief Changes item by index.
     *
     * Nothing will happen, if index out of range.
     *
     * @param idx Index of item to change.
     * @param item New item.
     */
    virtual void change_item(std::uint16_t idx, CommandItem item) noexcept = 0;

    /**
     * @brief Returns index of item with selected key.
     *
     * @param key Item's key to search.
     *
     * @return Index of item, or -1 if there is no item with selected key.
     */
    [[nodiscard]]
    virtual std::int16_t indexOf(std::string key) const noexcept = 0;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Returns vector of command items.
     *
     * @return Command items.
     */
    [[nodiscard]]
    virtual std::vector<CommandItem> items() const noexcept = 0;

    /**
     * @brief Converts command to string.
     *
     * @return Command via string representation.
     */
    [[nodiscard]]
    virtual std::string str() const noexcept = 0;

    /**
     * @brief Marks command with selected tag.
     *
     * @param tag Command tag.
     */
    virtual void set_tag(std::string tag) noexcept = 0;

    /**
     * @brief Returns command tag.
     *
     * @return Command tag.
     */
    [[nodiscard]]
    virtual std::string get_tag() const noexcept = 0;

    /**
     * @brief Tries to parse selected string to command items and fill it.
     *
     * @param command_str Command via string.
     */
    virtual void set(const std::string &command_str) noexcept = 0;

#pragma endregion Accessors / Mutators
};
}
