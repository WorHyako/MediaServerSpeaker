#include "Interfaces/IMovableControl.hpp"

using namespace Mss::Gui::Controls;

IMovableControl::IMovableControl(QWidget *parent) noexcept
    : IControl{ parent },
      WidgetTransformComponent{ this } {
}

#pragma region Accessors / Mutators

void IMovableControl::edit_mode(bool enable) noexcept {
    Components::WidgetTransformComponent::can_transform(enable);

    IControl::edit_mode(enable);
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void IMovableControl::mouseMoveEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::do_transform(e);

    IControl::mouseMoveEvent(e);
}

void IMovableControl::mouseReleaseEvent(QMouseEvent *e) {
    Components::WidgetTransformComponent::stop_transform();

    IControl::mouseReleaseEvent(e);
}

#pragma endregion Callbacks
