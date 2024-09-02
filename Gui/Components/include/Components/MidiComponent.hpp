#pragma once

#include <cstdint>

namespace Mss::Gui::Components {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class MidiComponent {
	public:
		/**
		 * @brief Ctor.
		 */
		MidiComponent() noexcept;

		/**
		 * @brief Dtor.
		 */
		virtual ~MidiComponent() = default;

		/**
		 * @brief
		 */
		void goMidiRoad() noexcept;

	private:
		std::uint8_t _midiKeyIdx;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t midiKeyIdx() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
