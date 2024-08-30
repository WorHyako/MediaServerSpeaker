#include "Midi/MidiRoad.hpp"

#include "Midi/MidiKeyboard.hpp"
#include "TemplateWrapper/Singleton.hpp"
#include "Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"

using namespace Mss::Backend::Midi;

MidiRoad::MidiRoad(std::uint8_t buttonId) noexcept
	: _buttonId(buttonId),
	  _isActive(false) {
}

void MidiRoad::go() noexcept {
	using WorOutCallback = Wor::Midi::CallbackInfo::ApcMiniOutCallbackInfo;

	auto &midiIn = Wor::TemplateWrapper::Singleton<Wor::Midi::MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}

	WorOutCallback out(_buttonId, _isActive ? _activeLed : _defaultLed);
	midiIn.send(out);

	_isActive = !_isActive;
}

#pragma region Accessors/Mutators

void MidiRoad::activeLed(Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed led) noexcept {
	_activeLed = led;
}

void MidiRoad::defaultLed(Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed led) noexcept {
	_defaultLed = led;
}

#pragma endregion Accessors/Mutators
