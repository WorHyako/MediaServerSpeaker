#include "Components/MidiComponent.hpp"

#include "Wor/Wrappers/Singleton.hpp"
#include "Midi/MidiRoadMap.hpp"

using namespace Mss::Gui::Components;

MidiComponent::MidiComponent() noexcept
	: _midiKeyIdx(0) {
}

void MidiComponent::goMidiRoad() noexcept {
	auto &roadMap = Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get();
	auto road = roadMap.midiRoad(_midiKeyIdx);
	road.go();
}

#pragma region Accessors/Mutators

void MidiComponent::midiKeyIdx(std::uint8_t midiKeyIdx) noexcept {
	_midiKeyIdx = midiKeyIdx;
}

std::uint8_t MidiComponent::midiKeyIdx() const noexcept {
	return _midiKeyIdx;
}

#pragma endregion Accessors/Mutators
