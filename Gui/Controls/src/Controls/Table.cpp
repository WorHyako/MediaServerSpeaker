#include "Table.hpp"

#include <QVBoxLayout>
#include <QPushButton>

#include "TableRow.hpp"

using namespace Mss::Gui::Controls;

Table::Table(QWidget *parent) noexcept
        : MovableBaseControl(parent),
          _button(nullptr),
          _rowsLayout(nullptr) {
    QWidget::resize(200, 300);

    auto layout = new QVBoxLayout;
    QWidget::setLayout(layout);

    _rowsLayout = new QVBoxLayout;
    layout->addLayout(_rowsLayout);

    addRow();

    auto buttonLayout = new QHBoxLayout;

    auto addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked, [this]() {
        addRow();
    });
    buttonLayout->addWidget(addButton);

    auto removeButton = new QPushButton("Remove");
    connect(removeButton, &QPushButton::clicked, [this]() {
        removeRow();
    });
    buttonLayout->addWidget(removeButton);

    layout->addLayout(buttonLayout);

    _button = new QPushButton("Table");
    connect(_button, &QPushButton::pressed, [this]() {
        std::ignore = Components::CommandComponent::getCommand()->execute(BaseControl::_socketName);
    });
    layout->addWidget(_button);
    layout->itemAt(2)->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Table::addRow(const QPair<QString, QString> &pair) noexcept {
    auto row = new TableRow(pair);
    connect(row, &TableRow::keyValueChanged, this, &Table::keyValueChange);

    _rowsLayout->addWidget(row);

    getCommand()->addItem({ row->getKeyValue().first.toStdString(), row->getKeyValue().second.toStdString() });
}

void Table::removeRow() noexcept {
    auto idx = _rowsLayout->count() - 1;
    auto row = _rowsLayout->itemAt(idx);
    _rowsLayout->removeItem(row);
    row->widget()->deleteLater();

    getCommand()->removeItem();
}

void Table::commandChanged() noexcept {
    clear();
    auto commandItems = Components::CommandComponent::getCommand()->getItems();
    std::for_each(std::begin(commandItems), std::end(commandItems), [this](const Backend::Command::CommandItem &item) {
        addRow({ item.key().c_str(), item.value().c_str() });
    });
    BaseControl::commandChanged();
}

void Table::clear() noexcept {
    while (_rowsLayout->count() > 0) {
        removeRow();
    }
}

void Table::keyValueChange(const QPair<QString, QString> &keyValue, TableRow *sender) {
    auto idx = _rowsLayout->indexOf(sender);
    auto command = Components::CommandComponent::getCommand();
    command->changeItem(idx, { keyValue.first.toStdString(), keyValue.second.toStdString() });
}

#pragma region Accessors/Mutators

void Table::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string Table::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
