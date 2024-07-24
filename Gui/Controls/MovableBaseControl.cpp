#include "MovableBaseControl.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;

MovableBaseControl::MovableBaseControl(QWidget *parent) noexcept
        : WidgetTransformComponent(this),
          BaseControl(parent) {
}

void MovableBaseControl::mouseMoveEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::doTransform(e);

    BaseControl::mouseMoveEvent(e);
}

void MovableBaseControl::mouseReleaseEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::stopTransform(e);

    BaseControl::mouseReleaseEvent(e);
}

void MovableBaseControl::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            std::ignore = _command->execute("127.0.0.1");
            break;
        case Qt::MouseButton::RightButton:
            _menu->popup(QWidget::mapToGlobal(e->pos()));
            break;
        default:
            break;
    }
}