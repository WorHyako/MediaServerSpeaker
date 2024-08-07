#include "ManagementTextableButton.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>

using namespace Mss::Gui::Controls;

ManagementTextableButton::ManagementTextableButton(QWidget *parent) noexcept
        : MovableBaseControl(parent),
          _textEdit(nullptr),
          _button(nullptr) {
    QWidget::resize(200, 200);

    auto layout = new QVBoxLayout;
    layout->setSpacing(8);
    QWidget::setLayout(layout);

    _button = new QPushButton("Event name");
    connect(_button, &QPushButton::pressed, [this]() {
        std::ignore = Components::CommandComponent::getCommand()->execute(BaseControl::_socketName);
    });
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_button);
    std::ignore = layout->setStretchFactor(_button, 5);

    _textEdit = new QTextEdit;
    _textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_textEdit);
    std::ignore = layout->setStretchFactor(_textEdit, 1);
}

void ManagementTextableButton::commandChanged() noexcept {
    auto value = getCommand()->getItems()[0].value();
    _textEdit->setText(value.c_str());
}

#pragma region Accessors/Mutators

void ManagementTextableButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string ManagementTextableButton::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
