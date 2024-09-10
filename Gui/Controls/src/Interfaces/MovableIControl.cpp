#include "Interfaces/IMovableControl.hpp"

using namespace Mss::Gui::Controls;

IMovableControl::IMovableControl(QWidget *parent) noexcept
	: IControl(parent),
	  WidgetTransformComponent(this) {
}

#pragma region Accessors/Mutators

void IMovableControl::editMode(bool enable) noexcept {
	Components::WidgetTransformComponent::canTransform(enable);

	IControl::editMode(enable);
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void IMovableControl::mouseMoveEvent(QMouseEvent *e) {
	Components::WidgetTransformComponent::doTransform(e);

	IControl::mouseMoveEvent(e);
}

void IMovableControl::mouseReleaseEvent(QMouseEvent *e) {
	Components::WidgetTransformComponent::stopTransform();

	IControl::mouseReleaseEvent(e);
}

#pragma endregion Callbacks
