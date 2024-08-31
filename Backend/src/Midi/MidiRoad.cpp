#include "Midi/MidiRoad.hpp"

#include "Wor/Midi/MidiKeyboard.hpp"
#include "Wor/Wrappers/Singleton.hpp"
#include "Wor/Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"

using namespace Mss::Backend::Midi;

MidiRoad::MidiRoad(std::uint8_t buttonId) noexcept
	: _buttonId(buttonId),
	  _isActive(false) {
}

void MidiRoad::go() noexcept {
	using WorOutCallback = Wor::Midi::CallbackInfo::ApcMiniOutCallbackInfo;

	auto &midiIn = Wor::Wrappers::Singleton<Wor::Midi::MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}

	WorOutCallback out(_buttonId, _isActive ? _activeLed : _defaultLed);
	midiIn.send(out);

	_isActive = !_isActive;
}

#pragma region Accessors/Mutators

Wor::Midi::CallbackInfo::MidiLed MidiRoad::activeLed() const noexcept {
	return _activeLed;
}

Wor::Midi::CallbackInfo::MidiLed MidiRoad::defaultLed() const noexcept {
	return _defaultLed;
}

void MidiRoad::activeLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept {
	_activeLed = led;
}

void MidiRoad::defaultLed(const Wor::Midi::CallbackInfo::MidiLed& led) noexcept {
	_defaultLed = led;
}

#pragma endregion Accessors/Mutators
