#include "Components/WidgetTransformComponent.hpp"

#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

using namespace Mss::Gui::Components;

WidgetTransformComponent::WidgetTransformComponent(QWidget *parent) noexcept
    : parent_{ parent },
      last_mouse_press_position_{ -1, -1 },
      can_transform_{ false } {
}

void WidgetTransformComponent::do_transform(QMouseEvent *e) noexcept {
    const auto mouse_new_pos{ parent_->mapToParent(e->pos()) };
    if (last_mouse_press_position_ == QPoint(-1, -1)) {
        last_mouse_press_position_ = mouse_new_pos;
        return;
    }
    const auto parent_owner{ parent_->parentWidget() };
    const auto delta_position{ mouse_new_pos - last_mouse_press_position_ };
    last_mouse_press_position_ = mouse_new_pos;

    if (can_transform_ && e->modifiers().testFlag(Qt::KeyboardModifier::AltModifier)) {
        const QPoint current_size{ parent_->width(), parent_->height() };
        const QPoint new_size{ current_size + delta_position };

        const QPoint max_size{ parent_owner->width(), parent_owner->height() };

        parent_->resize(
            { new_size.x() > 50 && new_size.x() < max_size.x() ? new_size.x() : current_size.x(),
              new_size.y() > 50 && new_size.y() < max_size.y() ? new_size.y() : current_size.y() }
        );

    } else if (can_transform_ && e->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier)) {
        const auto current_pos{ parent_->pos() };
        const auto new_pos{ current_pos + delta_position };

        const std::pair<bool, bool> move_condition{
            new_pos.x() > 0 && new_pos.x() < parent_owner->width() - parent_->width(),
            new_pos.y() > 0 && new_pos.y() < parent_owner->height() - parent_->height()
        };

        parent_->move(
            { move_condition.first ? new_pos.x() : current_pos.x(), move_condition.second ? new_pos.y() : current_pos.y() }
        );
    }
}

void WidgetTransformComponent::stop_transform() noexcept {
    last_mouse_press_position_ = { -1, -1 };
}

#pragma region Accessors / Mutators

void WidgetTransformComponent::can_transform(bool can_transform) noexcept {
    can_transform_ = can_transform;
}

#pragma endregion Accessors / Mutators
