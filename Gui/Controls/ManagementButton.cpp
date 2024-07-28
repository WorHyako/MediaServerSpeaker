#include "Controls/ManagementButton.hpp"

#include "Controls/ControlCreator.hpp"

#include <QMouseEvent>
#include <QVBoxLayout>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
        : MovableBaseControl(parent),
          _button(nullptr) {
    Components::WidgetTransformComponent::_canResize = true;
    Components::WidgetTransformComponent::_canMove = true;

    QWidget::resize(200, 200);

    _button = new QPushButton("Event name", this);
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    QWidget::setLayout(layout);

    layout->addWidget(_button);
}

#pragma region Accessors/Mutators

void ManagementButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string ManagementButton::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
