#include "Midi/MidiRoadMap.hpp"

#include "Hierarchy/Files.hpp"

#include "nlohmann/json.hpp"

#include "Wor/Json/JsonManager.hpp"

using namespace Mss::Backend::Midi;

void MidiRoadMap::addRoad(std::uint8_t midiKeyIdx, ServerRoad road) noexcept {
	_serverRoad[midiKeyIdx] = std::move(road);
}

MidiRoadMap::MidiRoadMap() noexcept
	: _buttonIdIdx(0) {
}

void MidiRoadMap::addRoad(std::uint8_t midiKeyIdx, MidiRoad road) noexcept {
	_midiRoad.emplace(std::pair(midiKeyIdx, std::move(road)));
}

void MidiRoadMap::transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &inCallbackInfo) noexcept {
	std::uint8_t buttonId = inCallbackInfo.vector().at(_buttonIdIdx);

	try {
		MidiRoad *midiRoad = &_midiRoad.at(buttonId);
		midiRoad->go();
	} catch (std::out_of_range &e) {

	}

	try {
		ServerRoad *serverRoad = &_serverRoad.at(buttonId);
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
	nlohmann::json json;
	std::ranges::for_each(_midiRoad,
						  [&json](const auto &road) {
							  const std::uint8_t roadKey = road.first;
							  const MidiRoad roadValue = road.second;
							  nlohmann::json keyJson;

							  nlohmann::json activeLedJson;
							  activeLedJson["color"] = roadValue.activeLed().color();
							  activeLedJson["mode"] = roadValue.activeLed().mode();

							  nlohmann::json defaultLedJson;
							  defaultLedJson["color"] = roadValue.defaultLed().color();
							  defaultLedJson["mode"] = roadValue.defaultLed().mode();

							  keyJson["active"] = activeLedJson;
							  keyJson["default"] = defaultLedJson;
							  json[std::to_string(roadKey)] = keyJson;
						  });

	std::string configPath = System::getResourcePath().data();
	std::ignore = Wor::Json::tryToSaveFile(configPath + "RoadMap/midi.json", json.dump());
}

void MidiRoadMap::load() noexcept {
	std::string configPath = System::getResourcePath().data();
	nlohmann::json json = Wor::Json::tryToLoadFile(configPath + "RoadMap/midi.json");
	auto itemsCount = json.size();
	for (std::size_t i = 0; i < itemsCount; i++) {
		nlohmann::json keyObject = json[std::to_string(i)];
		MidiRoad road(i);

		nlohmann::json activeLedObject = keyObject["active"];
		road.activeLed().color(activeLedObject["color"]);
		road.activeLed().mode(activeLedObject["mode"]);

		nlohmann::json defaultLedObject = keyObject["default"];
		road.defaultLed().color(defaultLedObject["color"]);
		road.defaultLed().mode(defaultLedObject["mode"]);
		addRoad(i, road);
	}
	std::ignore = 5;
}

#pragma region Accessors/Mutators

void MidiRoadMap::buttonIdIdx(std::uint8_t idx) noexcept {
	_buttonIdIdx = idx;
}

std::optional<MidiRoad> MidiRoadMap::midiRoad(std::uint8_t midiIdx) const noexcept {
	return _midiRoad.count(midiIdx)
			? _midiRoad.at(midiIdx)
			: std::optional<MidiRoad>();
}

std::optional<ServerRoad> MidiRoadMap::serverRoad(std::uint8_t midiIdx) const noexcept {
	return _serverRoad.count(midiIdx)
			? _serverRoad.at(midiIdx)
			: std::optional<ServerRoad>();
}

#pragma endregion Accessors/Mutators
