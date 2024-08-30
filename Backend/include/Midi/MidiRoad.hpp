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

		Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed _activeLed;

		Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed _defaultLed;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param led
		 */
		void activeLed(Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed led) noexcept;

		/**
		 * @brief
		 *
		 * @param led
		 */
		void defaultLed(Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed led) noexcept;

#pragma endregion Accessors/Mutators
	};
}
