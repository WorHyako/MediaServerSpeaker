#include "Midi/MidiRoadMap.hpp"

using namespace Mss::Backend::Midi;

void MidiRoadMap::addRoad(std::uint8_t midiKeyIdx, ServerRoad road) noexcept {
	_serverRoad[midiKeyIdx] = std::move(road);
}

void MidiRoadMap::addRoad(std::uint8_t midiKeyIdx, MidiRoad road) noexcept {
	_midiRoad.emplace(std::pair(midiKeyIdx, std::move(road)));
}

void MidiRoadMap::transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &inCallbackInfo) noexcept {
	std::uint8_t roadIdx = inCallbackInfo.buttonId();

	try {
		MidiRoad *midiRoad = &_midiRoad.at(roadIdx);
		midiRoad->go();
	} catch (std::out_of_range &e) {

	}

	try {
		ServerRoad *serverRoad = &_serverRoad.at(roadIdx);
		serverRoad->go();
	} catch (std::out_of_range &e) {

	}
}

void MidiRoadMap::clear() noexcept {
	_serverRoad.clear();
}

void MidiRoadMap::removeRoad(std::uint8_t midiKeyIdx) noexcept {
	_serverRoad.erase(midiKeyIdx);
	_midiRoad.erase(midiKeyIdx);
}

void MidiRoadMap::save() const noexcept {
}

void MidiRoadMap::load() noexcept {
}
