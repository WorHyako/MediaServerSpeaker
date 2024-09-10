#include "QuickButton.hpp"

#include <QMouseEvent>
#include <QPushButton>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;
using namespace Mss::Backend;

QuickButton::QuickButton(QWidget *parent) noexcept
        : IControl(parent),
          _button(new QPushButton(this)) {
}

#pragma region Accessors/Mutators

void QuickButton::text(std::string text) noexcept {
	_button->setText(text.c_str());
}

std::string QuickButton::text() const noexcept {
	return _button->text().toUtf8().constData();
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void QuickButton::commandChanged() noexcept {

}

#pragma endregion Callbacks
