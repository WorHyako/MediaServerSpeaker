#include "ManagementTextableButton.hpp"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace Mss::Gui::Controls;

ManagementTextableButton::ManagementTextableButton(QWidget *parent) noexcept
    : IMovableControl{ parent },
      text_edit_{ nullptr },
      button_{ nullptr } {
    QWidget::resize(200, 200);

    auto layout{ new QVBoxLayout };
    layout->setSpacing(8);
    QWidget::setLayout(layout);

    button_ = new QPushButton("Event name");
    std::ignore = connect(button_, &QPushButton::pressed, [this]() {
        std::ignore = CommandComponent::execute();
    });
    button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(button_);
    std::ignore = layout->setStretchFactor(button_, 5);

    text_edit_ = new QLineEdit;
    text_edit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(text_edit_);
    std::ignore = layout->setStretchFactor(text_edit_, 1);
}

#pragma region Accessors / Mutators

void ManagementTextableButton::set_text(std::string text) noexcept {
    button_->setText(text.c_str());
}

std::string ManagementTextableButton::get_text() const noexcept {
    return button_->text().toUtf8().constData();
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void ManagementTextableButton::command_changed() noexcept {
    const auto command_items{ CommandComponent::command()->items() };
    text_edit_->setText(command_items.empty() ? "" : command_items[0].value().c_str());
}

#pragma endregion Callbacks
