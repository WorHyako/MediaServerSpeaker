#include "Pages/KeyboardLayout/ApcMiniButton.hpp"

#include "Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"

#include "Midi/MidiKeyboard.hpp"
#include "TemplateWrapper/Singleton.hpp"
#include "Midi/CallbackInfo/ApcMiniLed.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

using ApcMiniLed = CallbackInfo::ApcMini::ApcMiniLed;

ApcMiniButton::ApcMiniButton(const QString &buttonText, QWidget *parent) noexcept
	: BaseMidiButton(buttonText, parent) {
}

#pragma region Callbacks

void ApcMiniButton::mousePressEvent(QMouseEvent *e) noexcept {
	auto &midiIn = Wor::TemplateWrapper::Singleton<MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}
	auto *currentLed =
			reinterpret_cast<CallbackInfo::ApcMini::ApcMiniLed *>(_isActive ? &_activeColor : &_defaultColor);
	CallbackInfo::ApcMiniOutCallbackInfo callbackInfo(_midiKeyIdx, *currentLed);
	midiIn.send(callbackInfo);

	setStyleSheet(std::format("background-color: rgb({}, {}, {});",
							  currentLed->rgb().x,
							  currentLed->rgb().y,
							  currentLed->rgb().z).c_str());
	_isActive = !_isActive;

	QPushButton::mousePressEvent(e);
}

#pragma endregion Callbacks
