#include "Components/WidgetTransformComponent.hpp"

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

using namespace Mss::Gui::Components;

WidgetTransformComponent::WidgetTransformComponent(QWidget *parent) noexcept
	: _parent(parent),
	  _lastMousePressPosition({-1, -1}),
	  _canTransform(false) {
}

void WidgetTransformComponent::doTransform(QMouseEvent *e) noexcept {
	auto mouseNewPos = _parent->mapToParent(e->pos());
	if (_lastMousePressPosition == QPoint(-1, -1)) {
		_lastMousePressPosition = mouseNewPos;
		return;
	}
	const auto parentOwner = _parent->parentWidget();
	const auto deltaPosition = mouseNewPos - _lastMousePressPosition;
	_lastMousePressPosition = mouseNewPos;

	if (_canTransform && e->modifiers().testFlag(Qt::KeyboardModifier::AltModifier)) {
		const QPoint currentSize = {_parent->width(), _parent->height()};
		const QPoint newSize = currentSize + deltaPosition;

		const QPoint maxSize = {parentOwner->width(), parentOwner->height()};

		_parent->resize({newSize.x() > 50 && newSize.x() < maxSize.x() ? newSize.x() : currentSize.x(),
						 newSize.y() > 50 && newSize.y() < maxSize.y() ? newSize.y() : currentSize.y()});

	} else if (_canTransform && e->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier)) {
		const auto currentPos = _parent->pos();
		const auto newPos = currentPos + deltaPosition;

		const std::pair<bool, bool> moveCondition = {
				newPos.x() > 0 && newPos.x() < parentOwner->width() - _parent->width(),
				newPos.y() > 0 && newPos.y() < parentOwner->height() - _parent->height()};

		_parent->move({moveCondition.first ? newPos.x() : currentPos.x(),
					   moveCondition.second ? newPos.y() : currentPos.y()});
	}
}

void WidgetTransformComponent::stopTransform() noexcept {
	_lastMousePressPosition = {-1, -1};
}

#pragma region Accessors/Mutators

void WidgetTransformComponent::canTransform(bool canTransform) noexcept {
	_canTransform = canTransform;
}

#pragma endregion Accessors/Mutators
