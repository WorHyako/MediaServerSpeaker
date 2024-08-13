#include "Interfaces/IMovableControl.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;

IMovableControl::IMovableControl(QWidget *parent) noexcept
        : WidgetTransformComponent(this),
          IControl(parent) {
}

#pragma region Callbacks

void IMovableControl::mouseMoveEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::doTransform(e);

    IControl::mouseMoveEvent(e);
}

void IMovableControl::mouseReleaseEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::stopTransform(e);

    IControl::mouseReleaseEvent(e);
}

void IMovableControl::editMode(bool enable) noexcept {
    Components::WidgetTransformComponent::canTransform(enable);

    IControl::editMode(enable);
}

#pragma endregion Callbacks
