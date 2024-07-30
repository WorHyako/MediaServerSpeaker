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
    connect(_button, &QPushButton::pressed, [this](){
        std::ignore = Components::CommandComponent::getCommand()->execute(BaseControl::_socketName);
    });
    layout->addWidget(_button);
    layout->itemAt(2)->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Table::addRow() noexcept {
    auto row = new TableRow;

    _rowsLayout->addWidget(row);
}

void Table::removeRow() noexcept {
    auto idx = _rowsLayout->count() - 1;
    auto row = _rowsLayout->itemAt(idx);
    row->widget()->deleteLater();
}

#pragma region Accessors/Mutators

void Table::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string Table::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
