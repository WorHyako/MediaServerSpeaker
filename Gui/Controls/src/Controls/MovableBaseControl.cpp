#include "MovableBaseControl.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;

MovableBaseControl::MovableBaseControl(QWidget *parent) noexcept
	: WidgetTransformComponent(this),
	  BaseControl(parent) {
}

void MovableBaseControl::editMode(bool enable) noexcept {
	auto children = QWidget::children();
	std::for_each(std::begin(children),
				  std::end(children),
				  [&enable, this](QObject *each) {
					  auto child = dynamic_cast<QWidget *>(each);
					  if (!child) {
						  return;
					  }
					  child->setAttribute(Qt::WA_TransparentForMouseEvents, enable);
					  Components::WidgetTransformComponent::canTransform(enable);
				  });
}

#pragma region Callbacks

void MovableBaseControl::mouseMoveEvent(QMouseEvent *e) {
	Components::WidgetTransformComponent::doTransform(e);

	BaseControl::mouseMoveEvent(e);
}

void MovableBaseControl::mouseReleaseEvent(QMouseEvent *e) {
	Components::WidgetTransformComponent::stopTransform(e);

	BaseControl::mouseReleaseEvent(e);
}

#pragma endregion Callbacks
