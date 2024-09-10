#pragma once

#include "Wor/Midi/CallbackInfo/ApcMiniLed.hpp"

namespace Mss::Backend::Midi {
	/**
	 * @brief	Object to control midi launchpad signals.
	 *			<p>
	 *			Controls active/passive status of launchpad's midi button.
	 *			<p>
	 *			Store roads in road map object.
	 *
	 * @usage
	 * @code
	 *			MidiRoad road;
	 *			road.activeLed(led1);
	 *			road.defaultLed(led2);
	 *			road.go();
	 * @endcode
	 *
	 * @see		@code MidiRoadMap @endcode
	 *
	 * @author	WorHyako
	 */
	class MidiRoad final {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	buttonId	Midi button id.
		 */
		explicit MidiRoad(std::uint8_t buttonId) noexcept;

		/**
		 * @brief	Sends out message to launchpad if it's possible.
		 *			<p>
		 *			Change active status via internal class field @code _isActive @endcode .
		 */
		void go() noexcept;

	private:
		/**
		 * @brief	Midi button's id.
		 */
		std::uint8_t _buttonId;

		/**
		 * @brief	Current state of midi button.
		 */
		bool _isActive;

		/**
		 * @brief	Led when button is active.
		 */
		Wor::Midi::CallbackInfo::MidiLed _activeLed;

		/**
		 * @brief	Led when button is passive.
		 */
		Wor::Midi::CallbackInfo::MidiLed _defaultLed;

	public:
#pragma region Accessors/Mutators
		/**
		 * @brief	Active led accessor.
		 *
		 * @return	Active led.
		 */
		[[nodiscard]]
		Wor::Midi::CallbackInfo::MidiLed activeLed() const noexcept;

		/**
		 * @brief	Default led accessor.
		 *
		 * @return	Default led.
		 */
		[[nodiscard]]
		Wor::Midi::CallbackInfo::MidiLed defaultLed() const noexcept;

		/**
		 * @brief	Active led mutator.
		 *
		 * @param	led New led.
		 */
		void activeLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept;

		/**
		 * @brief	Default led mutator
		 *
		 * @param	led New led.
		 */
		void defaultLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept;

#pragma endregion Accessors/Mutators
	};
}
