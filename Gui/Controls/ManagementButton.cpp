#include "Controls/ManagementButton.hpp"

#include "ContextMenu/ControlContextMenu.hpp"

#include "Controls/ControlCreator.hpp"

#include <QMouseEvent>
#include <QGridLayout>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
        : MovableBaseControl(parent),
          _button(nullptr) {
    Components::WidgetTransformComponent::_canResize = true;
    Components::WidgetTransformComponent::_canMove = true;

    QWidget::resize(200, 200);

    auto layout = new QVBoxLayout;
    QWidget::setLayout(layout);

    _button = new QPushButton("Button");
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_button);
}

void ManagementButton::mouseMoveEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::doTransform(e);

    MovableBaseControl::mouseMoveEvent(e);
}

void ManagementButton::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    if (e->modifiers() == Qt::Modifier::CTRL) {
        return;
    }
    switch (button) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton: {
            auto menu = Controls::ControlCreator<ContextMenu::ControlContextMenu>::create(this);
            menu->popup(QWidget::mapToGlobal(e->pos()));
        }
            break;
        default:
            break;
    }

    MovableBaseControl::mousePressEvent(e);
}

void ManagementButton::mouseReleaseEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::stopTransform(e);

    MovableBaseControl::mouseReleaseEvent(e);
}

void ManagementButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string ManagementButton::getText() const noexcept {
    return _button->text().toStdString();
}
