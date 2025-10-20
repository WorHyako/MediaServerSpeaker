#include "Midi/MidiRoad.hpp"

#include "Wor/Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"
#include "Wor/Midi/MidiKeyboard.hpp"
#include "Wor/Wrappers/Singleton.hpp"

using namespace Mss::Backend::Midi;

MidiRoad::MidiRoad(std::uint8_t button_id) noexcept
    : button_id_{button_id},
      is_active_{false} {
}

void MidiRoad::go() noexcept {
    using WorOutCallback = Wor::Midi::CallbackInfo::ApcMiniOutCallbackInfo;

    auto &midi_in { Wor::Wrappers::Singleton<Wor::Midi::MidiKeyboard>::get()};
    if (!midi_in.isOpen()) {
        return;
    }

    const WorOutCallback out{button_id_, is_active_ ? active_led_ : default_led_};
    midi_in.send(out);

    is_active_ = !is_active_;
}

#pragma region Accessors / Mutators

Wor::Midi::CallbackInfo::MidiLed MidiRoad::get_active_led() const noexcept {
    return active_led_;
}

Wor::Midi::CallbackInfo::MidiLed MidiRoad::get_default_led() const noexcept {
    return default_led_;
}

void MidiRoad::set_active_led(const Wor::Midi::CallbackInfo::MidiLed &led) noexcept {
    active_led_ = led;
}

void MidiRoad::set_default_led(const Wor::Midi::CallbackInfo::MidiLed &led) noexcept {
    default_led_ = led;
}

#pragma endregion Accessors / Mutators
