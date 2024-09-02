#include "ControlProperty.hpp"

#include "Interfaces/IMovableControl.hpp"

#include "Style/WorStyle.hpp"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

using namespace Mss::Gui::Controls::Dialogs;
using namespace Mss::Backend::Command;

ControlProperty::ControlProperty(QWidget *parent) noexcept
	: QDialog(parent),
	  _commandLayout(nullptr),
	  _control(dynamic_cast<Controls::IMovableControl *>(parent)),
	  _midiButtonId(0) {
	if (!_control) {
		QDialog::deleteLater();
		return;
	}

	QDialog::setWindowTitle(parent->accessibleName());

	QDialog::setStyleSheet(Style::getWorStyle().c_str());
	auto vLayout = new QVBoxLayout(this);
	QDialog::setLayout(vLayout);
	vLayout->setSpacing(5);
	_testCommand = std::make_unique<BaseCommand>();
	_testCommand->set(_control->command()->str());
	_controlName = _control->text();
	_midiButtonId = _control->midiKeyIdx();

	{
		/**
		 * Control name
		 */
		auto layout = new QHBoxLayout;

		auto text = new QTextEdit(_controlName.c_str());
		layout->addWidget(text);

		std::ignore = connect(text,
							  &QTextEdit::textChanged,
							  [this, text]() {
								  _controlName = text->toPlainText().toUtf8().constData();
							  });

		vLayout->addLayout(layout);
	}

	/**
	 * MidiIdx
	 */
	{
		auto layout = new QHBoxLayout;
		auto text = new QTextEdit(QString::number(_control->midiKeyIdx()));
		std::ignore = connect(text,
							  &QTextEdit::textChanged,
							  [&midiButtonId = _midiButtonId, text]() {
								  midiButtonId = text->toPlainText().toInt();
							  });
		layout->addWidget(text);

		vLayout->addLayout(layout);
	}

	auto commandTag = new QTextEdit(_testCommand->tag().c_str());
	std::ignore = connect(commandTag,
						  &QTextEdit::textChanged,
						  [commandTag, this]() {
							  _testCommand->tag(commandTag->toPlainText().toUtf8().constData());
							  emit fullCommandChanged(_testCommand->str().c_str());
						  });
	vLayout->addWidget(commandTag);

	{
		/**
		 * Command items layout command
		 */
		_commandLayout = new QVBoxLayout(vLayout->widget());

		auto controlItems = _testCommand->items();
		std::ranges::for_each(controlItems,
							  [this](const CommandItem &each) {
								  addCommandItemHLayout(each, false);
							  });
	}
	vLayout->addLayout(_commandLayout);

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
	vLayout->addLayout(buttonsLayout);

	/**
	 * Full command widget
	 */
	auto fullCommand = new QTextEdit(_testCommand->str().c_str());
	fullCommand->setFixedHeight(50);
	std::ignore = connect(this, SIGNAL(fullCommandChanged(QString)), fullCommand, SLOT(setText(QString)));
	fullCommand->setEnabled(false);
	vLayout->addWidget(fullCommand);

	auto sessionName = new QTextEdit(_control->sessionName().c_str());
	std::ignore = connect(sessionName,
						  &QTextEdit::textChanged,
						  [this, sessionName]() {
							  _sessionName = sessionName->toPlainText().toUtf8().constData();
						  });
	vLayout->addWidget(sessionName);

	{
		/**
		 * Common buttons
		 */
		auto layout = new QHBoxLayout;
		auto okButton = new QPushButton("Ok");
		std::ignore = connect(okButton,
							  &QPushButton::pressed,
							  [this]() {
								  applyChanged();
							  });
		layout->addWidget(okButton);

		auto cancelButton = new QPushButton("Cancel");
		std::ignore = connect(cancelButton,
							  &QPushButton::pressed,
							  [this]() {
								  QDialog::close();
							  });
		layout->addWidget(cancelButton);

		vLayout->addLayout(layout);
	}

	emit fullCommandChanged(_testCommand->str().c_str());
}

void ControlProperty::addCommandItemHLayout(const CommandItem &item, bool unique) noexcept {
	auto hLayout = new QHBoxLayout();
	if (unique) {
		auto idx = _testCommand->indexOf(item.key());
		if (idx != -1) {
			return;
		}
		_testCommand->addItem(item);
	}

	auto keyText = new QTextEdit(item.key().c_str());
	std::ignore = connect(keyText,
						  &QTextEdit::textChanged,
						  [keyText, hLayout, this]() {
							  auto idx = _commandLayout->indexOf(hLayout);
							  auto value = _testCommand->items()[idx].value();
							  emit refreshCommand(idx, {keyText->toPlainText().toUtf8().constData(), value});
						  });

	keyText->setStyleSheet(Style::getTextEditStyle().data());
	hLayout->addWidget(keyText);

	auto valueText = new QTextEdit(item.value().c_str());
	std::ignore = connect(valueText,
						  &QTextEdit::textChanged,
						  [valueText, hLayout, this]() {
							  auto idx = _commandLayout->indexOf(hLayout);
							  auto key = _testCommand->items()[idx].key();
							  emit refreshCommand(idx, {key, valueText->toPlainText().toUtf8().constData()});
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

void ControlProperty::applyChanged() noexcept {
	_control->command(_testCommand.release());
	emit _control->commandChanged();

	_control->text(_controlName);
	_control->sessionName(_sessionName);

	_control->midiKeyIdx(_midiButtonId);
	_control->createServerRoad();

	QDialog::close();
}

#pragma region Callbacks

void ControlProperty::refreshCommand(std::uint16_t idx, const CommandItem &item) {
	_testCommand->changeItem(idx, item);

	emit fullCommandChanged(_testCommand->str().c_str());
}

#pragma endregion Callbacks
