#include "Pages/KeyboardLayout/BaseMidiButton.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiButton::BaseMidiButton(const QString &buttonText, QWidget *parent) noexcept
	: QPushButton(buttonText, parent),
	  _activeColor(-1),
	  _defaultColor(-1),
	  _colorMode(-1),
	  _midiKeyIdx(-1),
	  _isActive(false) {
	QPushButton::setAutoFillBackground(true);
	QPushButton::setStyleSheet("background-color: rgb(100, 100, 100);");
}
