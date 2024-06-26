#include "Controls/ManagementButton.hpp"

#include <QMouseEvent>
#include <QTextBlock>

using namespace MSS::Gui::Controls;
using namespace MSS::Gui;

ManagementButton::ManagementButton(QWidget *parent)
        : Button(parent),
          _isResizable(true) {
    Components::WidgetTransformComponent::_canResize = true;
    Components::WidgetTransformComponent::_canMove = true;

    QPushButton::resize(200, 100);
}

void ManagementButton::mouseMoveEvent(QMouseEvent *e) {

    Button::mouseMoveEvent(e);
}

void ManagementButton::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton:
            break;
        default:
            break;
    }

    Button::mousePressEvent(e);
}

void ManagementButton::mouseReleaseEvent(QMouseEvent *e) {

    Button::mouseReleaseEvent(e);
}
