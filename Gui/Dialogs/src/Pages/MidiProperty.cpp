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

	auto idLayout = new QHBoxLayout;
	auto idLabel = new QLabel("Id:");
	idLayout->addWidget(idLabel);
	_idText = new QTextEdit;
	_idText->setFixedHeight(30);
	_idText->setEnabled(false);
	idLayout->addWidget(_idText);
	propertiesLayout->addLayout(idLayout);

	auto valueLayout = new QHBoxLayout;
	auto valueLabel = new QLabel("Value:");
	valueLayout->addWidget(valueLabel);
	auto valueText = new QTextEdit;
	valueText->setFixedHeight(30);
	valueLayout->addWidget(valueText);
	propertiesLayout->addLayout(valueLayout);

	auto activeColorLayout = new QHBoxLayout;
	auto activeColorLabel = new QLabel("Active color:");
	activeColorLayout->addWidget(activeColorLabel);
	_activeColorComboBox = new QComboBox;
	activeColorLayout->addWidget(_activeColorComboBox);
	propertiesLayout->addLayout(activeColorLayout);

	auto defaultColorLayout = new QHBoxLayout;
	auto defaultColorLabel = new QLabel("Default color:");
	defaultColorLayout->addWidget(defaultColorLabel);
	_defaultColorComboBox = new QComboBox;
	defaultColorLayout->addWidget(_defaultColorComboBox);
	propertiesLayout->addLayout(defaultColorLayout);

	auto colorModeLayout = new QHBoxLayout;
	auto colorModeLabel = new QLabel("Color mode:");
	colorModeLayout->addWidget(colorModeLabel);
	_colorModeComboBox = new QComboBox;
	colorModeLayout->addWidget(_colorModeComboBox);
	propertiesLayout->addLayout(colorModeLayout);
}

#pragma region Accessors/Mutators

void MidiProperty::targetButton(KeyboardLayout::ApcMiniButton *button) noexcept {
	auto colors = Wor::Midi::CallbackInfo::ApcMini::availableColors();

	_button = button;
	_idText->setText(QString::number(_button->midiKeyIdx()));
	_activeColorComboBox->clear();
	connect(_activeColorComboBox,
			&QComboBox::currentIndexChanged,
			[button, colors](int idx) {
				auto it = std::begin(colors);
				std::advance(it, idx);
				button->activeColor(it->first);
			});
	_defaultColorComboBox->clear();
	connect(_defaultColorComboBox,
			&QComboBox::currentIndexChanged,
			[button, colors](int idx) {
				auto it = std::begin(colors);
				std::advance(it, idx);
				button->defaultColor(it->first);
			});
	_colorModeComboBox->clear();

	auto colorMods = Wor::Midi::CallbackInfo::ApcMini::availableColorMods();
	connect(_colorModeComboBox,
			&QComboBox::currentIndexChanged,
			[button, colorMods](int idx) {
				auto it = std::begin(colorMods);
				std::advance(it, idx);
				button->colorMode(it->first);
			});

	std::ranges::for_each(colorMods,
						  [&colorModeCombobox = _colorModeComboBox](
						  const std::pair<std::uint8_t, std::string> &colorMode) {
							  colorModeCombobox->addItem(colorMode.second.c_str());
						  });

	std::ranges::for_each(colors,
						  [&activeColorCombobox = _activeColorComboBox](
						  const std::pair<std::uint8_t, std::string> &color) {
							  activeColorCombobox->addItem(color.second.c_str());
						  });

	std::ranges::for_each(colors,
						  [&defaultColorCombobox = _defaultColorComboBox](
						  const std::pair<std::uint8_t, std::string> &color) {
							  defaultColorCombobox->addItem(color.second.c_str());
						  });
}

KeyboardLayout::ApcMiniButton *MidiProperty::targetButton() const noexcept {
	return _button;
}

#pragma endregion Accessors/Mutators
