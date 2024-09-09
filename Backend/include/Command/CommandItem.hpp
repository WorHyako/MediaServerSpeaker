#pragma once

#include <string>

namespace Mss::Backend::Command {

	/**
	 * @brief	Represents a pair of key-value command item.
	 *			<p>
	 *			In command string @code CommandItem @endcode looks like "...key=value..."
	 *
	 * @author	WorHyako
	 */
	class CommandItem final {
	public:
		/**
		 * @brief Ctor.
		 */
		CommandItem() noexcept = default;

		/**
		 * @brief	Ctor.
		 *
		 * @param	key		Key
		 *
		 * @param	value	Value
		 */
		CommandItem(std::string key, std::string value) noexcept;

		/**
		 * @brief Copy ctor.
		 */
		CommandItem(const CommandItem &) noexcept = default;

	private:
		std::string _key;

		std::string _value;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Key accessor
		 *
		 * @return	key
		 */
		[[nodiscard]]
		std::string key() const noexcept;

		/**
		 * @brief	Value accessor
		 *
		 * @return	value
		 */
		[[nodiscard]]
		std::string value() const noexcept;

		/**
		 * @brief	Checks for value emptiness.
		 *
		 * @return	@code true @endcode		CommandItem's value is empty.
		 *			<p>
		 *			@code false @endcode	CommandItem's value isn't empty.
		 */
		[[nodiscard]]
		bool empty() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
