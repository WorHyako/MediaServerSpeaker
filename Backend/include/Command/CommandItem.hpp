#pragma once

#include <string>

namespace Mss::Backend::Command {

/**
 * @brief Represents a pair of key-value command item.
 *
 * In command string CommandItem looks like "...key=value..."
 *
 * @author WorHyako
 */
class CommandItem final {
  public:
    /**
     * @brief Default constructor.
     */
    CommandItem() noexcept = default;

    /**
     * @brief Constructor with parameters.
     *
     * @param key Key.
     * @param value Value.
     */
    CommandItem(std::string key, std::string value) noexcept;

    /**
     * @brief Copy constructor.
     */
    CommandItem(const CommandItem &) noexcept = default;

  private:
    std::string key_;

    std::string value_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Returns the key.
     *
     * @return Key.
     */
    [[nodiscard]]
    std::string key() const noexcept;

    /**
     * @brief Returns the value.
     *
     * @return Value.
     */
    [[nodiscard]]
    std::string value() const noexcept;

    /**
     * @brief Checks for value emptiness.
     *
     * @return true CommandItem's value is empty.
     * @return false CommandItem's value isn't empty.
     */
    [[nodiscard]]
    bool empty() const noexcept;

#pragma endregion Accessors / Mutators
};
}
