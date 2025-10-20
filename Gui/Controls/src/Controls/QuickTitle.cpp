#include "QuickTitle.hpp"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

using namespace Mss::Gui::Controls;

QuickTitle::QuickTitle(QWidget *parent) noexcept
    : IControl{ parent },
      button_{ nullptr },
      text_edit_{ nullptr } {
    auto layout{ new QHBoxLayout };
    layout->setSpacing(3);
    QWidget::setLayout(layout);

    text_edit_ = new QLineEdit;
    text_edit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(text_edit_);
    std::ignore = layout->setStretchFactor(text_edit_, 5);

    button_ = new QPushButton("Send");
    button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(button_);
    auto buttonLayoutItem{ layout->itemAt(1) };
    buttonLayoutItem->setAlignment(Qt::AlignmentFlag::AlignCenter);
    std::ignore = layout->setStretchFactor(button_, 1);
}

#pragma region Accessors / Mutators

void QuickTitle::set_text(std::string text) noexcept {
    text_edit_->setText(text.c_str());
}

std::string QuickTitle::get_text() const noexcept {
    return text_edit_->text().toUtf8().constData();
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void QuickTitle::command_changed() noexcept {
}

#pragma endregion Callbacks
