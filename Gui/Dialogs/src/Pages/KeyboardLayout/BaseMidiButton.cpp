#include "Pages/KeyboardLayout/BaseMidiButton.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiButton::BaseMidiButton(const QString &buttonText, QWidget *parent) noexcept
	: QPushButton(buttonText, parent),
	  _midiKeyIdx(0),
	  _isActive(false) {
	QPushButton::setAutoFillBackground(true);
	QPushButton::setStyleSheet("background-color: rgb(100, 100, 100);");
}

#pragma region Accessors/Mutators

void BaseMidiButton::midiKeyIdx(std::uint8_t midiKeyIdx) noexcept {
	_midiKeyIdx = midiKeyIdx;
}

std::uint8_t BaseMidiButton::midiKeyIdx() const noexcept {
	return _midiKeyIdx;
}

void BaseMidiButton::activeColor(MidiLed color) noexcept {
	_activeColor = color;
}

BaseMidiButton::MidiLed BaseMidiButton::activeColor() const noexcept {
	return _activeColor;
}

void BaseMidiButton::defaultColor(MidiLed color) noexcept {
	_defaultColor = color;
}

BaseMidiButton::MidiLed BaseMidiButton::defaultColor() const noexcept {
	return _defaultColor;
}

#pragma endregion Accessors/Mutators
