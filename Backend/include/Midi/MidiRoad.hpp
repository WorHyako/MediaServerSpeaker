#pragma once

#include "Midi/CallbackInfo/ApcMiniLed.hpp"

namespace Mss::Backend::Midi {
	/**
	 * @brief
	 *
	 * @author
	 */
	class MidiRoad final {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param buttonId
		 */
		explicit MidiRoad(std::uint8_t buttonId) noexcept;

		/**
		 * @brief
		 */
		void go() noexcept;

	private:
		std::uint8_t _buttonId;

		bool _isActive;

		Wor::Midi::CallbackInfo::MidiLed _activeLed;

		Wor::Midi::CallbackInfo::MidiLed _defaultLed;

	public:
#pragma region Accessors/Mutators
		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		Wor::Midi::CallbackInfo::MidiLed activeLed() const noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		Wor::Midi::CallbackInfo::MidiLed defaultLed() const noexcept;

		/**
		 * @brief
		 *
		 * @param led
		 */
		void activeLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept;

		/**
		 * @brief
		 *
		 * @param led
		 */
		void defaultLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept;

#pragma endregion Accessors/Mutators
	};
}
