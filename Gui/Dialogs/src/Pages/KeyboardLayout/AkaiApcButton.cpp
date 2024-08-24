#include "Pages/KeyboardLayout/AkaiApcButton.hpp"

#include "Midi/MidiKeyboard.hpp"
#include "TemplateWrapper/Singleton.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

AkaiApcButton::AkaiApcButton(const QString &buttonText, QWidget *parent) noexcept
	: QPushButton(buttonText, parent),
	  _midiKeyIdx(-1) {
	QPushButton::setAutoFillBackground(true);
	QPushButton::setStyleSheet("background-color: rgb(100, 100, 100);");
}

#pragma region Accessors/Mutators

void AkaiApcButton::midiKeyIdx(std::uint8_t midiKeyIdx) noexcept {
	_midiKeyIdx = midiKeyIdx;
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void AkaiApcButton::mousePressEvent(QMouseEvent *event) noexcept {
	auto &midiIn = Wor::TemplateWrapper::Singleton<Wor::Midi::MidiKeyboard>::get();
	if (!midiIn.isOpen()) {
		return;
	}
	// midiIn.send();
}

#pragma endregion Callbacks
