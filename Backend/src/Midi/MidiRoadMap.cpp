module;

#include "Wor/Json/JsonManager.hpp"

#include <nlohmann/json.hpp>

module mss.backend:midi.MidiRoadMap.impl;
import :midi.MidiRoadMap;

import mss.project;
import worlib.midi;

using namespace Mss::Backend::Midi;

void MidiRoadMap::add_road(std::uint8_t midi_key_idx, ServerRoad road) noexcept {
    server_road_[midi_key_idx] = std::move(road);
}

MidiRoadMap::MidiRoadMap() noexcept
    : button_id_idx_{ 0 } {
}

void MidiRoadMap::add_road(std::uint8_t midi_key_idx, MidiRoad road) noexcept {
    midi_road_.emplace(std::pair(midi_key_idx, std::move(road)));
}

void MidiRoadMap::transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &in_callback_info) noexcept {
    const std::uint8_t button_id{ in_callback_info.vector().at(button_id_idx_) };

    try {
        MidiRoad *midi_road{ &midi_road_.at(button_id) };
        midi_road->go();
    } catch (std::out_of_range &e) {
    }

    try {
        ServerRoad *server_road{ &server_road_.at(button_id) };
        server_road->go();
    } catch (std::out_of_range &e) {
    }
}

void MidiRoadMap::clear() noexcept {
    server_road_.clear();
}

void MidiRoadMap::remove_road(std::uint8_t midi_key_idx) noexcept {
    server_road_.erase(midi_key_idx);
    midi_road_.erase(midi_key_idx);
}

void MidiRoadMap::save() const noexcept {
    nlohmann::json json;
    std::ranges::for_each(midi_road_, [&json](const auto &road) {
        const std::uint8_t road_key{ road.first };
        const MidiRoad road_value{ road.second };
        nlohmann::json key_json;

        nlohmann::json active_led_json;
        active_led_json["color"] = road_value.get_active_led().color();
        active_led_json["mode"] = road_value.get_active_led().mode();

        nlohmann::json default_led_json;
        default_led_json["color"] = road_value.get_default_led().color();
        default_led_json["mode"] = road_value.get_default_led().mode();

        key_json["active"] = active_led_json;
        key_json["default"] = default_led_json;
        json[std::to_string(road_key)] = key_json;
    });

    const std::string config_path{ System::get_resource_path().data() };
    std::ignore = Wor::Json::tryToSaveFile(config_path + "RoadMap/midi.json", json.dump());
}

void MidiRoadMap::load() noexcept {
    const std::string config_path{ System::get_resource_path().data() };
    nlohmann::json json{ Wor::Json::tryToLoadFile(config_path + "RoadMap/midi.json") };
    for (auto i{ 0 }; i < std::size(json); i++) {
        nlohmann::json key_object{ json[std::to_string(i)] };
        MidiRoad road(i);

        nlohmann::json active_led_object{ key_object["active"] };
        road.get_active_led().color(active_led_object["color"]);
        road.get_active_led().mode(active_led_object["mode"]);

        nlohmann::json default_led_object{ key_object["default"] };
        road.get_default_led().color(default_led_object["color"]);
        road.get_default_led().mode(default_led_object["mode"]);
        add_road(i, road);
    }
    std::ignore = 5;
}

#pragma region Accessors / Mutators

void MidiRoadMap::set_button_id_idx(std::uint8_t idx) noexcept {
    button_id_idx_ = idx;
}

std::optional<MidiRoad> MidiRoadMap::midi_road(std::uint8_t midi_idx) const noexcept {
    return midi_road_.contains(midi_idx) ? midi_road_.at(midi_idx) : std::optional<MidiRoad>();
}

std::optional<ServerRoad> MidiRoadMap::server_road(std::uint8_t midi_idx) const noexcept {
    return server_road_.contains(midi_idx) ? server_road_.at(midi_idx) : std::optional<ServerRoad>();
}

#pragma endregion Accessors / Mutators
