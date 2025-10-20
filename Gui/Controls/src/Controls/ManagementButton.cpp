#include "ManagementButton.hpp"

#include <QPushButton>
#include <QVBoxLayout>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
    : IMovableControl{ parent },
      button_{ nullptr } {
    QWidget::resize(200, 200);

    button_ = new QPushButton("Event name", this);
    button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    std::ignore = connect(button_, &QPushButton::pressed, [this]() {
        std::ignore = Components::CommandComponent::execute();
    });

    auto layout{ new QVBoxLayout };
    QWidget::setLayout(layout);

    layout->addWidget(button_);
}

#pragma region Accessors / Mutators

void ManagementButton::set_text(std::string text) noexcept {
    button_->setText(text.c_str());
}

std::string ManagementButton::get_text() const noexcept {
    return button_->text().toUtf8().constData();
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void ManagementButton::command_changed() noexcept {
}

#pragma endregion Callbacks
