#include "ManagementButton.hpp"

#include "Creators/ControlCreator.hpp"

#include <QVBoxLayout>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
        : MovableBaseControl(parent),
          _button(nullptr) {
    QWidget::resize(200, 200);

    _button = new QPushButton("Event name", this);
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(_button, &QPushButton::pressed, [this]() {
        std::ignore = Components::CommandComponent::_command->execute(BaseControl::_socketName);
    });

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
