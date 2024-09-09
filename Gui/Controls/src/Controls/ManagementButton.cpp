#include "ManagementButton.hpp"

#include <QVBoxLayout>
#include <QPushButton>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ManagementButton::ManagementButton(QWidget *parent) noexcept
	: IMovableControl(parent),
	  _button(nullptr) {
	QWidget::resize(200, 200);


	_button = new QPushButton("Event name", this);
	_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	std::ignore = connect(_button,
						  &QPushButton::pressed,
						  [this]() {
							  std::ignore = Components::CommandComponent::execute();
						  });

	auto layout = new QVBoxLayout;
	QWidget::setLayout(layout);

	layout->addWidget(_button);
}

#pragma region Accessors/Mutators

void ManagementButton::text(std::string text) noexcept {
	_button->setText(text.c_str());
}

std::string ManagementButton::text() const noexcept {
	return _button->text().toUtf8().constData();
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void ManagementButton::commandChanged() noexcept {

}

#pragma endregion Callbacks
