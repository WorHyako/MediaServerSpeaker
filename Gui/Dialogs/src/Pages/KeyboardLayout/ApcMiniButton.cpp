#include "Pages/KeyboardLayout/ApcMiniButton.hpp"

#include "Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"

#include "Midi/MidiKeyboard.hpp"
#include "TemplateWrapper/Singleton.hpp"
#include "Midi/CallbackInfo/ApcMiniInfo.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

using ApcMiniColor = CallbackInfo::ApcMini::Color;
using ApcMiniColorMode = CallbackInfo::ApcMini::ColorMode;

namespace {
	const std::string redRgb = "200, 0, 0";

	const std::string greenRgb = "0, 200, 0";

	const std::string yellowRgb = "255, 79, 0";

	const std::string noneRgb = "100, 100, 100";
}

ApcMiniButton::ApcMiniButton(const QString &buttonText, QWidget *parent) noexcept
	: BaseMidiButton(buttonText, parent) {
}

#pragma region Accessors/Mutators

void ApcMiniButton::midiKeyIdx(std::uint8_t midiKeyIdx) noexcept {
	_midiKeyIdx = midiKeyIdx;
}

std::uint8_t ApcMiniButton::midiKeyIdx() const noexcept {
	return _midiKeyIdx;
}

void ApcMiniButton::activeColor(std::uint8_t color) noexcept {
	_activeColor = color;
}

std::uint8_t ApcMiniButton::activeColor() const noexcept {
	return _activeColor;
}

void ApcMiniButton::defaultColor(std::uint8_t color) noexcept {
	_defaultColor = color;
}

std::uint8_t ApcMiniButton::defaultColor() const noexcept {
	return _defaultColor;
}

std::string ApcMiniButton::colorRgbStr() const noexcept {
	switch (static_cast<ApcMiniColor>(_isActive ? _activeColor : _defaultColor)) {
		case ApcMiniColor::Red:
			return ::redRgb;
		case ApcMiniColor::Green:
			return ::greenRgb;
		case ApcMiniColor::Yellow:
			return ::yellowRgb;
		default:
			return ::noneRgb;
	}
}

std::uint8_t ApcMiniButton::colorMode() const noexcept {
	return _colorMode;
}

void ApcMiniButton::colorMode(std::uint8_t colorMode) noexcept {
	_colorMode = colorMode;
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void ApcMiniButton::mousePressEvent(QMouseEvent *e) noexcept {
	auto &midiIn = Wor::TemplateWrapper::Singleton<MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}
	CallbackInfo::ApcMiniOutCallbackInfo callbackInfo(
			_midiKeyIdx,
			static_cast<ApcMiniColor>(_isActive ? _activeColor : _defaultColor),
			static_cast<ApcMiniColorMode>(_colorMode));
	midiIn.send(callbackInfo);

	_isActive = !_isActive;

	QPushButton::mousePressEvent(e);
}

#pragma endregion Callbacks
