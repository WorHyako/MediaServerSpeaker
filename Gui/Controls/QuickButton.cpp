#include "Controls/QuickButton.hpp"

#include "Controls/ControlCreator.hpp"

#include "Command/BaseCommand.hpp"
#include "Command/CommandBuilder.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;
using namespace Mss::Backend;

QuickButton::QuickButton(QWidget *parent) noexcept
        : BaseControl(parent),
          _button(nullptr) {
    _button = new QPushButton(this);
    _button->show();

    BaseControl::_command = std::move(Command::CommandBuilder<Command::BaseCommand>::build());
}

void QuickButton::mouseMoveEvent(QMouseEvent *e) {
    BaseControl::mouseMoveEvent(e);
}

#pragma region Accessors/Mutators

void QuickButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string QuickButton::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
