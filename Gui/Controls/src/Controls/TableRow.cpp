#include "Controls/TableRow.hpp"

#include <QHBoxLayout>
#include <QTextEdit>

using namespace Mss::Gui::Controls;

TableRow::TableRow(const QPair<QString, QString> &keyValue, QWidget *parent)
        : QWidget(parent) {
    auto layout = new QHBoxLayout;
    QWidget::setLayout(layout);

    auto keyText = new QTextEdit(keyValue.first.isEmpty() ? tr("key") : keyValue.first);
    layout->addWidget(keyText);

    auto valueText = new QTextEdit(keyValue.second.isEmpty() ? tr("value") : keyValue.second);
    layout->addWidget(valueText);

    connect(keyText, &QTextEdit::textChanged, [keyText, valueText, this]() {
        auto key = keyText->toPlainText();
        auto value = valueText->toPlainText();

        emit keyValueChanged({ key, value }, this);
    });

    connect(valueText, &QTextEdit::textChanged, [keyText, valueText, this]() {
        auto key = keyText->toPlainText();
        auto value = valueText->toPlainText();

        emit keyValueChanged({ key, value }, this);
    });
}

#pragma region Accessors/Mutators

QPair<QString, QString> TableRow::getKeyValue() const noexcept {
    auto layout = QWidget::layout();

    auto keyWidget = layout->itemAt(0)->widget();
    auto key = dynamic_cast<QTextEdit *>(keyWidget)->toPlainText();

    auto valueWidget = layout->itemAt(1)->widget();
    auto value = dynamic_cast<QTextEdit *>(valueWidget)->toPlainText();

    return { key, value };
}

void TableRow::setKeyValue(const QPair<QString, QString> &keyValue) noexcept {
    auto layout = QWidget::layout();

    auto keyWidget = layout->itemAt(0)->widget();
    dynamic_cast<QTextEdit *>(keyWidget)->setText(keyValue.first);

    auto valueWidget = layout->itemAt(1)->widget();
    dynamic_cast<QTextEdit *>(valueWidget)->setText(keyValue.second);
}

#pragma endregion Accessors/Mutators
