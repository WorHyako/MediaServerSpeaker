#include "Controls/ManagementButton.hpp"

#include "ContextMenu/ControlContextMenu.hpp"

#include "Controls/ControlCreator.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
        : Button(parent) {
    Components::WidgetTransformComponent::_canResize = true;
    Components::WidgetTransformComponent::_canMove = true;

    QPushButton::resize(200, 100);
}

void ManagementButton::mouseMoveEvent(QMouseEvent *e) {

    Button::mouseMoveEvent(e);
}

void ManagementButton::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton: {
            auto menu = Controls::ControlCreator<ContextMenu::ControlContextMenu>::create(this);
            menu->popup(QWidget::mapToGlobal(e->pos()));
        }
            break;
        default:
            break;
    }

    Button::mousePressEvent(e);
}

void ManagementButton::mouseReleaseEvent(QMouseEvent *e) {

    Button::mouseReleaseEvent(e);
}
