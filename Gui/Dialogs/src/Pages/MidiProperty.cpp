#include "Pages/MidiProperty.hpp"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

#include "Midi/CallbackInfo/ApcMiniInfo.hpp"

using namespace Mss::Gui::Dialogs::Pages;

MidiProperty::MidiProperty(QWidget *parent) noexcept
	: QWidget(parent),
	  _button(nullptr) {
	auto propertiesLayout = new QVBoxLayout;
	QWidget::setLayout(propertiesLayout);

	auto titleLabel = new QLabel("Properties");
	propertiesLayout->addWidget(titleLabel);
	{
		auto layout = new QHBoxLayout;
		auto label = new QLabel("Id:");
		layout->addWidget(label);
		_idText = new QTextEdit;
		_idText->setFixedHeight(30);
		_idText->setEnabled(false);
		layout->addWidget(_idText);
		propertiesLayout->addLayout(layout);
	}
	{
		auto layout = new QHBoxLayout;
		auto label = new QLabel("Active color:");
		layout->addWidget(label);
		_activeColorComboBox = new QComboBox;
		layout->addWidget(_activeColorComboBox);
		propertiesLayout->addLayout(layout);
	}
	{
		auto layout = new QHBoxLayout;
		auto label = new QLabel("Default color:");
		layout->addWidget(label);
		_defaultColorComboBox = new QComboBox;
		layout->addWidget(_defaultColorComboBox);
		propertiesLayout->addLayout(layout);
	}
}

#pragma region Accessors/Mutators

void MidiProperty::targetButton(KeyboardLayout::BaseMidiButton *button) noexcept {
	_button = button;
	_idText->setText(QString::number(_button->midiKeyIdx()));

	auto colors = Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed::availableLeds();

	_activeColorComboBox->clear();
	_activeColorComboBox->disconnect();

	_defaultColorComboBox->clear();
	_defaultColorComboBox->disconnect();

	std::ranges::for_each(colors,
						  [&colorCombobox = _activeColorComboBox](
						  const Wor::Midi::CallbackInfo::MidiLed &color) {
							  auto itemText = std::format("{} {}", color.colorName(), color.modeName());
							  colorCombobox->addItem(itemText.c_str());
						  });
	auto currentActiveColorIt = std::find_if(std::begin(colors),
											 std::end(colors),
											 [button](const Wor::Midi::CallbackInfo::MidiLed &each) {
												 return each == button->activeColor();
											 });
	std::uint8_t activeColorIdx = std::distance(std::begin(colors), currentActiveColorIt);
	_activeColorComboBox->setCurrentIndex(activeColorIdx);

	std::ranges::for_each(colors,
						  [&colorCombobox = _defaultColorComboBox](
						  const Wor::Midi::CallbackInfo::MidiLed &color) {
							  auto itemText = std::format("{} {}", color.colorName(), color.modeName());
							  colorCombobox->addItem(itemText.c_str());
						  });
	auto currentDefaultColorIt = std::find_if(std::begin(colors),
											  std::end(colors),
											  [button](const Wor::Midi::CallbackInfo::MidiLed &each) {
												  return each == button->defaultColor();
											  });
	std::uint8_t defaultColorIdx = std::distance(std::begin(colors), currentDefaultColorIt);
	_defaultColorComboBox->setCurrentIndex(defaultColorIdx);

	std::ignore = connect(_activeColorComboBox,
						  &QComboBox::currentIndexChanged,
						  [button, colors](int idx) {
							  if (idx == -1) {
								  return;
							  }
							  button->activeColor(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
						  });

	std::ignore = connect(_defaultColorComboBox,
						  &QComboBox::currentIndexChanged,
						  [button, colors](int idx) {
							  if (idx == -1) {
								  return;
							  }
							  button->defaultColor(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
						  });
}

KeyboardLayout::BaseMidiButton *MidiProperty::targetButton() const noexcept {
	return _button;
}

#pragma endregion Accessors/Mutators
