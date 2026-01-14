#include "Components/MidiComponent.hpp"

#include "Wor/Wrappers/Singleton.hpp"

import mss.backend;

using namespace Mss::Gui::Components;

MidiComponent::MidiComponent() noexcept
    : midi_key_idx_{ 0 } {
}

void MidiComponent::go_midi_road() noexcept {
    if (midi_key_idx_ < 0) {
        return;
    }
    const auto &road_map{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
    auto road{ road_map.midi_road(midi_key_idx_) };
    if (!road.has_value()) {
        return;
    }
    road.value().go();
}

#pragma region Accessors / Mutators

void MidiComponent::set_midi_key_idx(std::uint8_t midi_button_id) noexcept {
    midi_key_idx_ = midi_button_id;
}

std::uint8_t MidiComponent::get_midi_key_idx() const noexcept {
    return midi_key_idx_;
}

#pragma endregion Accessors / Mutators
