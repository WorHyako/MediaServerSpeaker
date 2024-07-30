#include "Table.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

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
    layout->addWidget(_button);
    layout->itemAt(2)->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Table::addRow() noexcept {
    auto hLayout = new QHBoxLayout;

    auto keyText = new QTextEdit("Key");
    hLayout->addWidget(keyText);

    auto valueText = new QTextEdit("Value");
    hLayout->addWidget(valueText);

    _rowsLayout->addLayout(hLayout);
}

void Table::removeRow() noexcept {
    auto rowLayout = dynamic_cast<QLayout *>(_rowsLayout->children().last());

    while (auto item = rowLayout->takeAt(0)) {
        rowLayout->removeItem(item);
        auto widget = item->widget();
        widget->deleteLater();
    }
    _rowsLayout->removeItem(rowLayout);
}

#pragma region Accessors/Mutators

void Table::setText(std::string text) noexcept {
    _button->setText(text.c_str());
}

std::string Table::getText() const noexcept {
    return _button->text().toStdString();
}

#pragma endregion Accessors/Mutators
