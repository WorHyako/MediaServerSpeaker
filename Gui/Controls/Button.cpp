#include "Controls/Button.hpp"

#include "Actions/RenameAction.hpp"

#include <QMenu>
#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

Button::Button(QWidget *parent) noexcept
        : QPushButton(parent),
          Components::WidgetTransformComponent(this) {
}

void Button::mouseMoveEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::doTransform(e);

    QPushButton::mouseMoveEvent(e);
}

void Button::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            std::printf("Left ");
            break;
        case Qt::MouseButton::RightButton: {
            auto menu = new QMenu(this);
            auto renameAction = new Actions::RenameAction(menu, this);
            auto deleteAction = new QAction("Delete");
            menu->addActions({ renameAction, deleteAction });
            menu->popup(mapToGlobal(e->pos()));
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

void Button::mouseReleaseEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::stopTransform(e);

    QPushButton::mouseReleaseEvent(e);
}

