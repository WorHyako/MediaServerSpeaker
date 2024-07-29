#include "BaseControl.hpp"

#include "ControlCreator.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

BaseControl::BaseControl(QWidget *parent) noexcept
        : QWidget(parent),
          _menu(Controls::ControlCreator<ContextMenu::ControlContextMenu>::create(this)),
          _socketName("127.0.0.1") {
    QWidget::setObjectName("WorControl");
}

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
