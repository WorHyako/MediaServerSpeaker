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
        std::ignore = Components::CommandComponent::command()->execute(Components::CommandComponent::sessionName());
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
    auto value = Components::CommandComponent::command()->items()[0].value();
    _textEdit->setText(value.c_str());
}

#pragma region Accessors/Mutators

void ManagementTextableButton::text(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string ManagementTextableButton::text() const noexcept {
    return _button->text().toUtf8().constData();
}

#pragma endregion Accessors/Mutators
