#pragma once

#include <cstdint>

namespace Mss::Gui::Components {
	/**
	 * @brief	Object separates all operations with midi launchpad events.
	 *			<p>
	 *			Orients just for inheritance existing.
	 *
	 * @usage
	 * @code
	 *			std::uint8_t midiKeyId = ...;
	 *			MidiComponent::midiKeyId(midiKeyIdx);
	 *			MidiComponent::goRoad();
	 * @endcode
	 *
	 * @author	WorHyako
	 *
	 * @see		@code MidiRoad @endcode
	 */
	class MidiComponent {
	public:
		/**
		 * @brief	Ctor.
		 */
		MidiComponent() noexcept;

		/**
		 * @brief	Dtor.
		 */
		virtual ~MidiComponent() = default;

		/**
		 * @brief	Try to go midi road with current midi button id
		 *			if it exists in road map.
		 */
		void goMidiRoad() noexcept;

	private:
		std::uint8_t _midiKeyIdx;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Midi button id mutator.
		 *
		 * @param	midiButtonId	Midi button id.
		 */
		void midiKeyIdx(std::uint8_t midiButtonId) noexcept;

		/**
		 * @brief	Midi button id accessor.
		 *
		 * @return	Midi button id.
		 */
		[[nodiscard]]
		std::uint8_t midiKeyIdx() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
