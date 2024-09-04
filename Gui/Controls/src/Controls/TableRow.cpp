#include "Controls/TableRow.hpp"

#include <QHBoxLayout>
#include <QLineEdit>

using namespace Mss::Gui::Controls;

TableRow::TableRow(const QPair<QString, QString> &keyValue, QWidget *parent)
	: QWidget(parent) {
	auto layout = new QHBoxLayout;
	QWidget::setLayout(layout);

	auto keyText = new QLineEdit(keyValue.first.isEmpty() ? tr("key") : keyValue.first);
	layout->addWidget(keyText);

	auto valueText = new QLineEdit(keyValue.second.isEmpty() ? tr("value") : keyValue.second);
	layout->addWidget(valueText);

	std::ignore = connect(keyText,
						  &QLineEdit::textChanged,
						  [keyText, valueText, this]() {
							  auto key = keyText->text();
							  auto value = valueText->text();

							  emit keyValueChanged({key, value}, this);
						  });

	std::ignore = connect(valueText,
						  &QLineEdit::textChanged,
						  [keyText, valueText, this]() {
							  auto key = keyText->text();
							  auto value = valueText->text();

							  emit keyValueChanged({key, value}, this);
						  });
}

#pragma region Accessors/Mutators

QPair<QString, QString> TableRow::keyValue() const noexcept {
	auto layout = QWidget::layout();

	auto keyWidget = layout->itemAt(0)->widget();
	auto key = dynamic_cast<QLineEdit *>(keyWidget)->text();

	auto valueWidget = layout->itemAt(1)->widget();
	auto value = dynamic_cast<QLineEdit *>(valueWidget)->text();

	return {key, value};
}

void TableRow::keyValue(const QPair<QString, QString> &keyValue) noexcept {
	auto layout = QWidget::layout();

	auto keyWidget = layout->itemAt(0)->widget();
	dynamic_cast<QLineEdit *>(keyWidget)->setText(keyValue.first);

	auto valueWidget = layout->itemAt(1)->widget();
	dynamic_cast<QLineEdit *>(valueWidget)->setText(keyValue.second);
}

#pragma endregion Accessors/Mutators
