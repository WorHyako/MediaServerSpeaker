#include "ManagementTextableButton.hpp"

#include <QHBoxLayout>

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
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_button);
    std::ignore = layout->setStretchFactor(_button, 5);

    _textEdit = new QTextEdit;
    _textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_textEdit);
    std::ignore = layout->setStretchFactor(_textEdit, 1);
}

#pragma region Accessors/Mutators

void ManagementTextableButton::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string ManagementTextableButton::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
