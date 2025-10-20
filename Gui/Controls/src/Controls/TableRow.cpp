#include "Controls/TableRow.hpp"

#include <QHBoxLayout>
#include <QLineEdit>

using namespace Mss::Gui::Controls;

TableRow::TableRow(const QPair<QString, QString> &key_value, QWidget *parent)
    : QWidget{parent} {
    auto layout{ new QHBoxLayout };
    QWidget::setLayout(layout);

    auto key_text{ new QLineEdit(key_value.first.isEmpty() ? tr("key") : key_value.first) };
    layout->addWidget(key_text);

    auto value_text{ new QLineEdit(key_value.second.isEmpty() ? tr("value") : key_value.second) };
    layout->addWidget(value_text);

    std::ignore = connect(key_text, &QLineEdit::textChanged, [key_text, value_text, this]() {
        auto key{ key_text->text() };
        auto value{ value_text->text() };

        emit keyValueChanged({ key, value }, this);
    });

    std::ignore = connect(value_text, &QLineEdit::textChanged, [key_text, value_text, this]() {
        auto key{ key_text->text() };
        auto value{ value_text->text() };

        emit keyValueChanged({ key, value }, this);
    });
}

#pragma region Accessors / Mutators

QPair<QString, QString> TableRow::key_value() const noexcept {
    const auto layout{ QWidget::layout() };

    const auto key_widget{ layout->itemAt(0)->widget() };
    const auto key{ dynamic_cast<QLineEdit *>(key_widget)->text() };

    const auto value_widget{ layout->itemAt(1)->widget() };
    const auto value{ dynamic_cast<QLineEdit *>(value_widget)->text() };

    return { key, value };
}

void TableRow::key_value(const QPair<QString, QString> &key_value) noexcept {
    const auto layout{ QWidget::layout() };

    auto key_widget{ layout->itemAt(0)->widget() };
    dynamic_cast<QLineEdit *>(key_widget)->setText(key_value.first);

    auto value_widget = layout->itemAt(1)->widget();
    dynamic_cast<QLineEdit *>(value_widget)->setText(key_value.second);
}

#pragma endregion Accessors / Mutators
