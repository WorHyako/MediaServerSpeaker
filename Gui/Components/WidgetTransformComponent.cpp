#include "Components/WidgetTransformComponent.hpp"

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

using namespace Mss::Gui::Components;

WidgetTransformComponent::WidgetTransformComponent(QWidget *parent) :
        _parent(parent),
        _lastMousePressPosition({ -1, -1 }),
        _canResize(false),
        _canMove(false) {
}

void WidgetTransformComponent::doTransform(QMouseEvent *e) noexcept {
    if (_lastMousePressPosition == QPoint(-1, -1)) {
        _lastMousePressPosition = e->pos();
    }
    const auto parentOwner = _parent->parentWidget();
    const auto deltaPosition = e->pos() - _lastMousePressPosition;

    if (_canResize && e->modifiers().testFlag(Qt::KeyboardModifier::AltModifier)) {
        const QPoint currentSize = { _parent->width(), _parent->height() };
        const QPoint newSize = currentSize + deltaPosition;

        const QPoint maxSize = { parentOwner->width(), parentOwner->height() };

        _parent->resize({ newSize.x() > 50 && newSize.x() < maxSize.x() ? newSize.x() : currentSize.x(),
                          newSize.y() > 50 && newSize.y() < maxSize.y() ? newSize.y() : currentSize.y() });


    } else if (_canMove && e->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier)) {
        const auto currentPos = _parent->pos();
        const auto newPos = currentPos + deltaPosition;

        const std::pair<bool, bool> moveCondition = {
                newPos.x() > 0 && newPos.x() < parentOwner->width() - _parent->width(),
                newPos.y() > 0 && newPos.y() < parentOwner->height() - _parent->height() };

        _parent->move({ moveCondition.first ? newPos.x() : currentPos.x(),
                        moveCondition.second ? newPos.y() : currentPos.y() });
    }

    _lastMousePressPosition = e->pos();
}

void WidgetTransformComponent::stopTransform(QMouseEvent *e) noexcept {
    _lastMousePressPosition = { -1, -1 };
}

void WidgetTransformComponent::setCanResize(bool canResize) noexcept {
    _canResize = canResize;
}

void WidgetTransformComponent::setCanMove(bool canMove) noexcept {
    _canMove = canMove;
}
