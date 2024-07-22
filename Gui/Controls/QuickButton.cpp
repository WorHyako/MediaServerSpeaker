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
        : QPushButton(parent),
          Components::WidgetTransformComponent(this) {
    BaseControl::_command = std::move(Command::CommandBuilder<Command::BaseCommand>::build());
}

void QuickButton::mouseMoveEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::doTransform(e);

    QPushButton::mouseMoveEvent(e);
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

    std::printf("Mouse button was pressed on Button with text: %s.\n", QPushButton::text().toStdString().c_str());

    QPushButton::mousePressEvent(e);
}

void QuickButton::mouseReleaseEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::stopTransform(e);

    QPushButton::mouseReleaseEvent(e);
}

void QuickButton::setText(std::string text) noexcept {
    QPushButton::setText(text.c_str());
}

std::string QuickButton::getText() const noexcept {
    return QPushButton::text().toStdString();
}
