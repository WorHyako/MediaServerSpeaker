#include "QuickTitle.hpp"

#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>

using namespace Mss::Gui::Controls;

QuickTitle::QuickTitle(QWidget *parent) noexcept
        : BaseControl(parent),
          _button(nullptr),
          _textEdit(nullptr) {
    QWidget::resize(100, 50);

    auto layout = new QHBoxLayout;
    layout->setSpacing(3);
    QWidget::setLayout(layout);

    _textEdit = new QTextEdit;
    _textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _textEdit->setFixedHeight(50);
    layout->addWidget(_textEdit);
    std::ignore = layout->setStretchFactor(_textEdit, 5);

    _button = new QPushButton("Send");
    _button->setFixedHeight(45);
    _button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(_button);
    auto buttonLayoutItem = layout->itemAt(1);
    buttonLayoutItem->setAlignment(Qt::AlignmentFlag::AlignCenter);
    std::ignore = layout->setStretchFactor(_button, 1);

}

#pragma region Accessors/Mutators

void QuickTitle::setText(std::string text) noexcept {
    _textEdit->setText(text.c_str());
}

std::string QuickTitle::getText() const noexcept {
    return _textEdit->toPlainText().toStdString();
}

#pragma endregion Accessors/Mutators
