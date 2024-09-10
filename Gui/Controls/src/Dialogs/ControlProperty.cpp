#include "ControlProperty.hpp"

#include <QLabel>

#include "Interfaces/IMovableControl.hpp"

#include "Style/WorStyle.hpp"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace Mss::Gui::Controls::Dialogs;
using namespace Mss::Backend::Command;

ControlProperty::ControlProperty(QWidget *parent) noexcept
	: QDialog(parent),
	  _control(dynamic_cast<Controls::IMovableControl *>(parent)),
	  _commandLayout(nullptr),
	  _midiButtonId(0) {
	if (!_control) {
		QDialog::deleteLater();
		return;
	}

	QDialog::setWindowTitle(parent->accessibleName());
	QDialog::setStyleSheet(Style::getWorStyle().c_str());

	auto hLayout = new QHBoxLayout;
	QDialog::setLayout(hLayout);
	auto labelLayout = new QVBoxLayout;
	auto textLayout = new QVBoxLayout;

	hLayout->addLayout(labelLayout);
	hLayout->addLayout(textLayout);

	_testCommand = std::make_unique<BaseCommand>();
	_testCommand->set(_control->command()->str());
	_controlName = _control->text();
	_midiButtonId = _control->midiKeyIdx();

	{
		/**
		 * Control name
		 */
		auto text = new QLineEdit(_controlName.c_str());
		textLayout->addWidget(text);

		auto label = new QLabel("Control Name");
		labelLayout->addWidget(label);

		std::ignore = connect(text,
							  &QLineEdit::textChanged,
							  [this, text]() {
								  _controlName = text->text().toUtf8().constData();
							  });
	}
	{
		/**
		 * MidiIdx
		 */
		auto text = new QLineEdit(QString::number(_control->midiKeyIdx()));
		textLayout->addWidget(text);

		auto label = new QLabel("Midi button ID");
		labelLayout->addWidget(label);

		std::ignore = connect(text,
							  &QLineEdit::textChanged,
							  [&midiButtonId = _midiButtonId, text]() {
								  midiButtonId = text->text().toInt();
							  });
	}
	{
		/**
		 * Command tag
		 */
		auto text = new QLineEdit(_testCommand->tag().c_str());
		textLayout->addWidget(text);

		auto label = new QLabel("Command tag");
		labelLayout->addWidget(label);

		std::ignore = connect(text,
							  &QLineEdit::textChanged,
							  [text, this]() {
								  _testCommand->tag(text->text().toUtf8().constData());
								  emit fullCommandChanged(_testCommand->str().c_str());
							  });
	}
	{
		/**
		 * Command items layout command
		 */
		_commandLayout = new QVBoxLayout;

		auto controlItems = _testCommand->items();
		std::ranges::for_each(controlItems,
							  [this](const CommandItem &each) {
								  addCommandItemHLayout(each, false);
							  });
		textLayout->addLayout(_commandLayout);
	}
	{
		/**
		 * Buttons layout for command items
		 */
		auto buttonsLayout = new QHBoxLayout;

		auto addCommandItemButton = new QPushButton("Add");
		std::ignore = connect(addCommandItemButton,
							  &QPushButton::pressed,
							  [this]() {
								  addCommandItemHLayout();
							  });
		buttonsLayout->addWidget(addCommandItemButton);
		textLayout->addLayout(buttonsLayout);
	}
	{
		/**
		 * Full command widget
		 */
		auto text = new QLineEdit(_testCommand->str().c_str());
		text->setEnabled(false);
		textLayout->addWidget(text);

		auto label = new QLabel("Full command");
		labelLayout->addWidget(label);

		std::ignore = connect(this, &ControlProperty::fullCommandChanged, text, &QLineEdit::textChanged);
	}
	{
		/**
		 * Session name
		 */
		auto text = new QLineEdit(_control->sessionName().c_str());
		textLayout->addWidget(text);

		auto label = new QLabel("Session name");
		labelLayout->addWidget(label);

		std::ignore = connect(text,
							  &QLineEdit::textChanged,
							  [this, text]() {
								  _sessionName = text->text().toUtf8().constData();
							  });
	}
	{
		/**
		 * Common buttons
		 */
		auto layout = new QHBoxLayout;
		auto okButton = new QPushButton("Ok");
		std::ignore = connect(okButton,&QPushButton::pressed, this, &ControlProperty::applyChanged);
		layout->addWidget(okButton);

		auto cancelButton = new QPushButton("Cancel");
		std::ignore = connect(cancelButton,
							  &QPushButton::pressed,
							  [this]() {
								  QDialog::close();
							  });
		layout->addWidget(cancelButton);

		textLayout->addLayout(layout);
	}

	emit fullCommandChanged(_testCommand->str().c_str());
}

void ControlProperty::addCommandItemHLayout(const CommandItem &item, bool unique) noexcept {
	auto hLayout = new QHBoxLayout;
	if (unique) {
		auto idx = _testCommand->indexOf(item.key());
		if (idx != -1) {
			return;
		}
		_testCommand->addItem(item);
	}

	auto keyText = new QLineEdit(item.key().c_str());
	std::ignore = connect(keyText,
						  &QLineEdit::textChanged,
						  [keyText, hLayout, this]() {
							  auto idx = _commandLayout->indexOf(hLayout);
							  auto value = _testCommand->items()[idx].value();
							  emit refreshCommand(idx, {keyText->text().toUtf8().constData(), value});
						  });

	keyText->setStyleSheet(Style::getTextEditStyle().data());
	hLayout->addWidget(keyText);

	auto valueText = new QLineEdit(item.value().c_str());
	std::ignore = connect(valueText,
						  &QLineEdit::textChanged,
						  [valueText, hLayout, this]() {
							  auto idx = _commandLayout->indexOf(hLayout);
							  auto key = _testCommand->items()[idx].key();
							  emit refreshCommand(idx, {key, valueText->text().toUtf8().constData()});
						  });
	hLayout->addWidget(valueText);

	auto removeButton = new QPushButton("Remove");
	removeButton->setFixedHeight(50);

	std::ignore = connect(removeButton,
						  &QPushButton::pressed,
						  [this, hLayout]() {
							  removeCommandItemHLayout(hLayout);
						  });
	hLayout->addWidget(removeButton);

	_commandLayout->addLayout(hLayout);
}

void ControlProperty::removeCommandItemHLayout(QHBoxLayout *hLayout) noexcept {
	auto idx = _commandLayout->indexOf(hLayout);
	_testCommand->removeItem(idx);

	_commandLayout->removeItem(hLayout);

	while (hLayout->count() > 0) {
		if (auto layoutItem = hLayout->takeAt(0)->widget()) {
			layoutItem->deleteLater();
		}
	}
	_commandLayout->update();

	emit fullCommandChanged(_testCommand->str().c_str());
}

#pragma region Callbacks

void ControlProperty::applyChanged() noexcept {
	_control->command(_testCommand.release());
	emit _control->commandChanged();

	_control->text(_controlName);
	_control->sessionName(_sessionName);

	_control->midiKeyIdx(_midiButtonId);
	_control->createServerRoad();

	QDialog::close();
}

void ControlProperty::refreshCommand(std::uint16_t idx, const CommandItem &item) {
	_testCommand->changeItem(idx, item);

	emit fullCommandChanged(_testCommand->str().c_str());
}

#pragma endregion Callbacks
