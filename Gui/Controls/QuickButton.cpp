#include "Controls/QuickButton.hpp"

#include "Controls/ControlCreator.hpp"

#include "ContextMenu/ControlContextMenu.hpp"

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

void QuickButton::mousePressEvent(QMouseEvent *e) {
    switch (e->button()) {
        case Qt::MouseButton::LeftButton:
            std::ignore = BaseControl::_command->execute("127.0.0.1");
            std::printf("Left ");
            break;
        case Qt::MouseButton::RightButton: {
            auto menu = ControlCreator<ContextMenu::ControlContextMenu>::create(this);
            menu->popup(QWidget::mapToGlobal(e->pos()));
            std::ignore = menu.release();
            std::printf("Right ");
            break;
        }
        default:
            std::printf("Some ");
            break;
    }

    std::printf("Mouse button was pressed on Button with text: %s.\n", _button->text().toStdString().c_str());

    BaseControl::mousePressEvent(e);
}

void QuickButton::mouseReleaseEvent(QMouseEvent *e) {

    BaseControl::mouseReleaseEvent(e);
}

void QuickButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string QuickButton::getText() const noexcept {
    return _button->text().toStdString();
}
