#include "MovableBaseControl.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;

MovableBaseControl::MovableBaseControl(QWidget *parent) noexcept
        : WidgetTransformComponent(this),
          BaseControl(parent) {
}

void MovableBaseControl::mouseMoveEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::doTransform(e);

    BaseControl::mouseMoveEvent(e);
}

void MovableBaseControl::mouseReleaseEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::stopTransform(e);

    BaseControl::mouseReleaseEvent(e);
}
