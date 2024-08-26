#include "Pages/KeyboardLayout/AkaiApcButton.hpp"

#include "Midi/MidiKeyboard.hpp"
#include "TemplateWrapper/Singleton.hpp"
#include "Midi/CallbackInfo/AkaiApcMiniInfo.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

using AkaiApcMiniColor = CallbackInfo::AkaiApcMini::Color;
using AkaiApcMiniColorType = CallbackInfo::AkaiApcMini::ColorType;

namespace {
	const std::string redRgb = "200, 0, 0";

	const std::string greenRgb = "0, 200, 0";

	const std::string yellowRgb = "255, 79, 0";

	const std::string noneRgb = "100, 100, 100";
}

AkaiApcButton::AkaiApcButton(const QString &buttonText, QWidget *parent) noexcept
	: IMidiButton(buttonText, parent),
	  _color(-1),
	  _colorType(-1) {
}

#pragma region Accessors/Mutators

void AkaiApcButton::midiKeyIdx(std::uint8_t midiKeyIdx) noexcept {
	_midiKeyIdx = midiKeyIdx;
}

void AkaiApcButton::color(std::uint16_t color) noexcept {
	_color = color;
}

std::string AkaiApcButton::colorRgbStr() noexcept {
	switch (static_cast<AkaiApcMiniColor>(_color)) {
		case AkaiApcMiniColor::Red:
			return ::redRgb;
		case AkaiApcMiniColor::Green:
			return ::greenRgb;
		case AkaiApcMiniColor::Yellow:
			return ::yellowRgb;
		default:
			return ::noneRgb;
	}
}

std::uint8_t AkaiApcButton::colorType() noexcept {
	return _colorType;
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void AkaiApcButton::mousePressEvent(QMouseEvent *event) noexcept {
	auto &midiIn = Wor::TemplateWrapper::Singleton<MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}
	CallbackInfo::AkaiApcOutCallbackInfo callbackInfo(
			_midiKeyIdx,
			static_cast<AkaiApcMiniColor>(_isActive ? _activeColor : _defaultColor),
			static_cast<AkaiApcMiniColorType>(_colorType));
	midiIn.send(callbackInfo);

	_isActive = !_isActive;
}

#pragma endregion Callbacks
