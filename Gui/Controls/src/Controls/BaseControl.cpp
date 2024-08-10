#include "BaseControl.hpp"

#include "Creators/ControlCreator.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

BaseControl::BaseControl(QWidget *parent) noexcept
        : QWidget(parent),
          _menu(Controls::ControlCreator<Menus::ControlContextMenu>::create(this)) {
    QWidget::setObjectName("WorControl");
}

#pragma region Callbacks

void BaseControl::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton:
            _menu->popup(QWidget::mapToGlobal(e->pos()));
            break;
        default:
            break;
    }
}

#pragma endregion Callbacks
