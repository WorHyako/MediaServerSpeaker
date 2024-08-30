#include "Pages/KeyboardLayout/ApcMiniButton.hpp"

#include "Midi/CallbackInfo/ApcMiniLed.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

using ApcMiniLed = CallbackInfo::ApcMini::ApcMiniLed;

ApcMiniButton::ApcMiniButton(const QString &buttonText, QWidget *parent) noexcept
	: BaseMidiButton(buttonText, parent) {
}
