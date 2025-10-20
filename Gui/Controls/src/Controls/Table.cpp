#include "Table.hpp"

#include "TableRow.hpp"

#include <QPushButton>
#include <QVBoxLayout>

using namespace Mss::Gui::Controls;

Table::Table(QWidget *parent) noexcept
    : IMovableControl{ parent },
      button_{ nullptr },
      rows_layout_{ nullptr } {
    QWidget::resize(200, 300);

    QWidget::setAutoFillBackground(true);

    auto layout{ new QVBoxLayout };
    QWidget::setLayout(layout);

    rows_layout_ = new QVBoxLayout;
    layout->addLayout(rows_layout_);

    add_row();

    auto button_layout{ new QHBoxLayout };

    const auto add_button{ new QPushButton("Add") };
    std::ignore = connect(add_button, &QPushButton::clicked, [this]() {
        add_row();
    });
    button_layout->addWidget(add_button);

    const auto remove_button{ new QPushButton("Remove") };
    std::ignore = connect(remove_button, &QPushButton::clicked, [this]() {
        remove_row();
    });
    button_layout->addWidget(remove_button);

    layout->addLayout(button_layout);

    button_ = new QPushButton("Table");
    std::ignore = connect(button_, &QPushButton::pressed, [this]() {
        std::ignore = Components::CommandComponent::execute();
    });
    layout->addWidget(button_);
    layout->itemAt(2)->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Table::add_row(const QPair<QString, QString> &pair) noexcept {
    auto row{ new TableRow(pair) };
    std::ignore = connect(row, &TableRow::keyValueChanged, this, &Table::key_value_change);

    rows_layout_->addWidget(row);

    Components::CommandComponent::command()->add_item(
        { row->key_value().first.toUtf8().constData(), row->key_value().second.toUtf8().constData() }
    );
}

void Table::remove_row() noexcept {
    const auto idx{ rows_layout_->count() - 1 };
    auto row{ rows_layout_->itemAt(idx) };
    rows_layout_->removeItem(row);
    row->widget()->deleteLater();

    Components::CommandComponent::command()->remove_item();
}

void Table::clear() noexcept {
    while (rows_layout_->count() > 0) {
        remove_row();
    }
}

void Table::key_value_change(const QPair<QString, QString> &key_value, TableRow *sender) {
    const auto idx{ rows_layout_->indexOf(sender) };
    auto command{ Components::CommandComponent::command() };
    command->change_item(idx, { key_value.first.toUtf8().constData(), key_value.second.toUtf8().constData() });
}

#pragma region Accessors / Mutators

void Table::set_text(std::string text) noexcept {
    button_->setText(std::move(text).c_str());
}

std::string Table::get_text() const noexcept {
    return button_->text().toUtf8().constData();
}

#pragma endregion Accessors / Mutators

#pragma region Callbacks

void Table::command_changed() noexcept {
    clear();
    auto command_items{ Components::CommandComponent::command()->items() };
    std::ranges::for_each(command_items, [this](const Backend::Command::CommandItem &item) {
        add_row({ item.key().c_str(), item.value().c_str() });
    });
}

#pragma endregion Callbacks
