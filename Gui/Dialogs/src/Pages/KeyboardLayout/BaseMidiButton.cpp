#include "Pages/KeyboardLayout/BaseMidiButton.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiButton::BaseMidiButton(const QString &buttonText, QWidget *parent) noexcept
	: QPushButton(buttonText, parent),
	  _activeColor({-1, -1}),
	  _defaultColor({-1, -1}),
	  _midiKeyIdx(-1),
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

void BaseMidiButton::activeColor(ColorValue color) noexcept {
	_activeColor = color;
}

BaseMidiButton::ColorValue BaseMidiButton::activeColor() const noexcept {
	return _activeColor;
}

void BaseMidiButton::defaultColor(ColorValue color) noexcept {
	_defaultColor = color;
}

BaseMidiButton::ColorValue BaseMidiButton::defaultColor() const noexcept {
	return _defaultColor;
}

#pragma endregion Accessors/Mutators
