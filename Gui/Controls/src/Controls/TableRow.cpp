#include "Controls/TableRow.hpp"

#include <QHBoxLayout>
#include <QTextEdit>

using namespace Mss::Gui::Controls;

TableRow::TableRow(QWidget *parent)
        : QWidget(parent) {
    auto layout = new QHBoxLayout;
    QWidget::setLayout(layout);

    auto keyText = new QTextEdit(tr("key"));
    layout->addWidget(keyText);

    auto valueText = new QTextEdit(tr("value"));
    layout->addWidget(valueText);
}

TableRow::TableRow(const QString &key, const QString &value, QWidget *parent)
        : QWidget(parent) {
    auto layout = new QHBoxLayout;
    QWidget::setLayout(layout);

    auto keyText = new QTextEdit(key);
    layout->addWidget(keyText);

    auto valueText = new QTextEdit(value);
    layout->addWidget(valueText);
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
