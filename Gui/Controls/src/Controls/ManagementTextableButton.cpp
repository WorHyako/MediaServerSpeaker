#include "ManagementTextableButton.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

using namespace Mss::Gui::Controls;

ManagementTextableButton::ManagementTextableButton(QWidget *parent) noexcept
	: IMovableControl(parent),
	  _textEdit(nullptr),
	  _button(nullptr) {
	QWidget::resize(200, 200);

	auto layout = new QVBoxLayout;
	layout->setSpacing(8);
	QWidget::setLayout(layout);

	_button = new QPushButton("Event name");
	std::ignore = connect(_button,
						  &QPushButton::pressed,
						  [this]() {
							  std::ignore = Components::CommandComponent::execute();
						  });
	_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(_button);
	std::ignore = layout->setStretchFactor(_button, 5);

	_textEdit = new QLineEdit;
	_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(_textEdit);
	std::ignore = layout->setStretchFactor(_textEdit, 1);
}

#pragma region Accessors/Mutators

void ManagementTextableButton::text(std::string text) noexcept {
	_button->setText(text.c_str());
}

std::string ManagementTextableButton::text() const noexcept {
	return _button->text().toUtf8().constData();
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void ManagementTextableButton::commandChanged() noexcept {
	auto commandItems = Components::CommandComponent::command()->items();
	_textEdit->setText(commandItems.empty()
			? ""
			: commandItems[0].value().c_str());
}

#pragma endregion Callbacks
