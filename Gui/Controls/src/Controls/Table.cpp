#include "Table.hpp"

#include <QVBoxLayout>
#include <QPushButton>

#include "TableRow.hpp"

using namespace Mss::Gui::Controls;

Table::Table(QWidget *parent) noexcept
	: IMovableControl(parent),
	  _button(nullptr),
	  _rowsLayout(nullptr) {
	QWidget::resize(200, 300);

	QWidget::setAutoFillBackground(true);

	auto layout = new QVBoxLayout;
	QWidget::setLayout(layout);

	_rowsLayout = new QVBoxLayout;
	layout->addLayout(_rowsLayout);

	addRow();

	auto buttonLayout = new QHBoxLayout;

	auto addButton = new QPushButton("Add");
	std::ignore = connect(addButton,
						  &QPushButton::clicked,
						  [this]() {
							  addRow();
						  });
	buttonLayout->addWidget(addButton);

	auto removeButton = new QPushButton("Remove");
	std::ignore = connect(removeButton,
						  &QPushButton::clicked,
						  [this]() {
							  removeRow();
						  });
	buttonLayout->addWidget(removeButton);

	layout->addLayout(buttonLayout);

	_button = new QPushButton("Table");
	std::ignore = connect(_button,
						  &QPushButton::pressed,
						  [this]() {
							  std::ignore = Components::CommandComponent::execute();
						  });
	layout->addWidget(_button);
	layout->itemAt(2)->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Table::addRow(const QPair<QString, QString> &pair) noexcept {
	auto row = new TableRow(pair);
	std::ignore = connect(row, &TableRow::keyValueChanged, this, &Table::keyValueChange);

	_rowsLayout->addWidget(row);

	Components::CommandComponent::command()->addItem({row->keyValue().first.toUtf8().constData(),
													  row->keyValue().second.toUtf8().constData()});
}

void Table::removeRow() noexcept {
	auto idx = _rowsLayout->count() - 1;
	auto row = _rowsLayout->itemAt(idx);
	_rowsLayout->removeItem(row);
	row->widget()->deleteLater();

	Components::CommandComponent::command()->removeItem();
}

void Table::clear() noexcept {
	while (_rowsLayout->count() > 0) {
		removeRow();
	}
}

void Table::keyValueChange(const QPair<QString, QString> &keyValue, TableRow *sender) {
	auto idx = _rowsLayout->indexOf(sender);
	auto command = Components::CommandComponent::command();
	command->changeItem(idx, {keyValue.first.toUtf8().constData(), keyValue.second.toUtf8().constData()});
}

#pragma region Accessors/Mutators

void Table::text(std::string text) noexcept {
	_button->setText(text.c_str());
}

std::string Table::text() const noexcept {
	return _button->text().toUtf8().constData();
}

#pragma endregion Accessors/Mutators

#pragma region Callbacks

void Table::commandChanged() noexcept {
	clear();
	auto commandItems = Components::CommandComponent::command()->items();
	std::ranges::for_each(commandItems,
						  [this](const Backend::Command::CommandItem &item) {
							  addRow({item.key().c_str(), item.value().c_str()});
						  });
}

#pragma endregion Callbacks
