#include "Pages/KeyboardLayout/BaseMidiButton.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiButton::BaseMidiButton(const QString &button_text, QWidget *parent) noexcept
    : QPushButton{ button_text, parent },
      midi_key_idx_{ 0 },
      is_active_{ false } {
    QPushButton::setAutoFillBackground(true);
    QPushButton::setStyleSheet("background-color: rgb(100, 100, 100);");
}

#pragma region Accessors / Mutators

void BaseMidiButton::set_midi_key_idx(std::uint8_t midi_key_idx) noexcept {
    midi_key_idx_ = midi_key_idx;
}

std::uint8_t BaseMidiButton::get_midi_key_idx() const noexcept {
    return midi_key_idx_;
}

void BaseMidiButton::set_active_color(MidiLed color) noexcept {
    active_color_ = color;
}

BaseMidiButton::MidiLed BaseMidiButton::get_active_color() const noexcept {
    return active_color_;
}

void BaseMidiButton::set_default_color(MidiLed color) noexcept {
    default_color_ = color;
}

BaseMidiButton::MidiLed BaseMidiButton::get_default_color() const noexcept {
    return default_color_;
}

#pragma endregion Accessors / Mutators
