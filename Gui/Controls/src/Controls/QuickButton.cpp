#include "QuickButton.hpp"

#include <QMouseEvent>
#include <QPushButton>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;
using namespace Mss::Backend;

QuickButton::QuickButton(QWidget *parent) noexcept
        : BaseControl(parent),
          _button(nullptr) {
    _button = new QPushButton(this);
    _button->show();
}

void QuickButton::mouseMoveEvent(QMouseEvent *e) {
    BaseControl::mouseMoveEvent(e);
}

#pragma region Accessors/Mutators

void QuickButton::text(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string QuickButton::text() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
