#include "Components/MidiComponent.hpp"

#include "Wor/Wrappers/Singleton.hpp"
#include "Midi/MidiRoadMap.hpp"

using namespace Mss::Gui::Components;

MidiComponent::MidiComponent() noexcept
	: _midiKeyIdx(0) {
}

void MidiComponent::goMidiRoad() noexcept {
	if (_midiKeyIdx < 0) {
		return;
	}
	auto &roadMap = Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get();
	auto road = roadMap.midiRoad(_midiKeyIdx);
	if (!road.has_value()) {
		return;
	}
	road.value().go();
}

#pragma region Accessors/Mutators

void MidiComponent::midiKeyIdx(std::uint8_t midiButtonId) noexcept {
	_midiKeyIdx = midiButtonId;
}

std::uint8_t MidiComponent::midiKeyIdx() const noexcept {
	return _midiKeyIdx;
}

#pragma endregion Accessors/Mutators
