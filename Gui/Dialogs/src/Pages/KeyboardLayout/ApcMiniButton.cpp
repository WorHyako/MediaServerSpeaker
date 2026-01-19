#include "Pages/KeyboardLayout/ApcMiniButton.hpp"

import worlib.midi;

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

using ApcMiniLed = CallbackInfo::ApcMini::ApcMiniLed;

ApcMiniButton::ApcMiniButton(const QString &button_text, QWidget *parent) noexcept
	: BaseMidiButton(button_text, parent) {
}
