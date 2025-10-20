#include "QuickButton.hpp"

#include <QMouseEvent>
#include <QPushButton>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;
using namespace Mss::Backend;

QuickButton::QuickButton(QWidget *parent) noexcept
    : IControl{ parent },
      button_{ new QPushButton(this) } {
}

#pragma region Accessors / Mutators

void QuickButton::set_text(std::string text) noexcept {
    button_->setText(text.c_str());
}

std::string QuickButton::get_text() const noexcept {
    return button_->text().toUtf8().constData();
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void QuickButton::command_changed() noexcept {
}

#pragma endregion Callbacks
