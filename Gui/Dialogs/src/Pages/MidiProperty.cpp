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
		auto activeColorModeLabel = new QLabel("Active color mode:");
		layout->addWidget(activeColorModeLabel);
		_activeColorModeComboBox = new QComboBox;
		layout->addWidget(_activeColorModeComboBox);
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
	{
		auto layout = new QHBoxLayout;
		auto label = new QLabel("Default color mode:");
		layout->addWidget(label);
		_defaultColorModeComboBox = new QComboBox;
		layout->addWidget(_defaultColorModeComboBox);
		propertiesLayout->addLayout(layout);
	}
}

#pragma region Accessors/Mutators

void MidiProperty::targetButton(KeyboardLayout::ApcMiniButton *button) noexcept {
	auto colors = Wor::Midi::CallbackInfo::ApcMini::availableColors();

	_button = button;
	_idText->setText(QString::number(_button->midiKeyIdx()));
	_activeColorComboBox->clear();
	_activeColorComboBox->disconnect();
	connect(_activeColorComboBox,
			&QComboBox::currentIndexChanged,
			[button, colors](int idx) {
				auto it = std::begin(colors);
				std::advance(it, idx);
				auto currentMode = button->activeColor().second;
				button->activeColor({it->first, currentMode});
			});

	_defaultColorComboBox->clear();
	_defaultColorComboBox->disconnect();
	connect(_defaultColorComboBox,
			&QComboBox::currentIndexChanged,
			[button, colors](int idx) {
				auto it = std::begin(colors);
				std::advance(it, idx);
				auto currentMode = button->activeColor().second;
				button->defaultColor({it->first, currentMode});
			});

	auto colorMods = Wor::Midi::CallbackInfo::ApcMini::availableColorMods();
	_activeColorModeComboBox->clear();
	_activeColorModeComboBox->disconnect();
	connect(_activeColorModeComboBox,
			&QComboBox::currentIndexChanged,
			[button, colorMods](int idx) {
				auto it = std::begin(colorMods);
				std::advance(it, idx);
				auto currentColor = button->activeColor().first;
				button->activeColor({currentColor, it->first});
			});

	_defaultColorModeComboBox->clear();
	_defaultColorModeComboBox->disconnect();
	connect(_defaultColorModeComboBox,
			&QComboBox::currentIndexChanged,
			[button, colorMods](int idx) {
				auto it = std::begin(colorMods);
				std::advance(it, idx);
				auto currentColor = button->activeColor().first;
				button->activeColor({currentColor, it->first});
			});

	std::ranges::for_each(colors,
						  [&colorCombobox = _activeColorComboBox](
						  const std::pair<std::uint8_t, std::string> &color) {
							  colorCombobox->addItem(color.second.c_str());
						  });

	std::ranges::for_each(colors,
						  [&colorCombobox = _defaultColorComboBox](
						  const std::pair<std::uint8_t, std::string> &color) {
							  colorCombobox->addItem(color.second.c_str());
						  });

	std::ranges::for_each(colorMods,
						  [&colorModeCombobox = _defaultColorComboBox](
						  const std::pair<std::uint8_t, std::string> &colorMode) {
							  colorModeCombobox->addItem(colorMode.second.c_str());
						  });

	std::ranges::for_each(colorMods,
						  [&colorModeCombobox = _defaultColorComboBox](
						  const std::pair<std::uint8_t, std::string> &colorMode) {
							  colorModeCombobox->addItem(colorMode.second.c_str());
						  });
}

KeyboardLayout::ApcMiniButton *MidiProperty::targetButton() const noexcept {
	return _button;
}

#pragma endregion Accessors/Mutators
