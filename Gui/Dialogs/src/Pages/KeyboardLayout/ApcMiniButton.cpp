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

std::string ApcMiniButton::colorRgbStr() const noexcept {
	switch (static_cast<ApcMiniColor>(_isActive ? _activeColor.first : _defaultColor.first)) {
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

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void ApcMiniButton::mousePressEvent(QMouseEvent *e) noexcept {
	auto &midiIn = Wor::TemplateWrapper::Singleton<MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}
	CallbackInfo::ApcMiniOutCallbackInfo callbackInfo(
			_midiKeyIdx,
			static_cast<ApcMiniColor>(_isActive ? _activeColor.first : _defaultColor.first),
			static_cast<ApcMiniColorMode>(_isActive ? _activeColor.second : _defaultColor.second));
	midiIn.send(callbackInfo);

	_isActive = !_isActive;

	QPushButton::mousePressEvent(e);
}

#pragma endregion Callbacks
