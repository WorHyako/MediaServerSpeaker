#include "Pages/MidiSettingsPage.hpp"

#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMouseEvent>

#include "Config/Config.hpp"
#include "Pages/KeyboardLayout/ApcMini.hpp"
#include "Pages/MidiProperty.hpp"

#include "Midi/MidiDeviceList.hpp"

using namespace Mss::Gui::Dialogs::Pages;

MidiSettingsPage::MidiSettingsPage(QWidget *parent) noexcept
	: QWidget(parent),
	  _keyboardLayoutWidget(nullptr),
	  _editMode(false) {
	auto mainLayout = new QHBoxLayout;
	QWidget::setLayout(mainLayout);

	auto keyboardLayout = new QVBoxLayout;
	{
		auto selectLayout = new QHBoxLayout;
		auto midiKeyboardLabel = new QLabel("Keyboards:");
		selectLayout->addWidget(midiKeyboardLabel);

		auto comboBox = new QComboBox;

		auto devices = Wor::Midi::MidiDeviceList::getKeyboards();
		std::ranges::for_each(devices,
							  [comboBox](const std::string &device) {
								  comboBox->addItem(device.c_str());
							  });

		selectLayout->addWidget(comboBox);

		auto showKeyboardLayout = new QPushButton("Show");
		connect(showKeyboardLayout,
				&QPushButton::clicked,
				[devices, comboBox,keyboardLayout, this]() {
					auto activeIdx = comboBox->currentIndex();
					if (activeIdx == -1) {
						return;
					}
					auto deviceName = devices[activeIdx];

					if (_keyboardLayoutWidget != nullptr) {
						layout()->removeWidget(_keyboardLayoutWidget);
						_keyboardLayoutWidget->deleteLater();
					}
					/**
					 * TODO: Implement enum casting
					 */
					if (deviceName == "APC MINI") {
						_keyboardLayoutWidget = new KeyboardLayout::ApcMini;
						keyboardLayout->addWidget(_keyboardLayoutWidget);
					}

					std::ignore = connect(_keyboardLayoutWidget,
										  &KeyboardLayout::BaseMidiLayout::midiKeyPressed,
										  [this](KeyboardLayout::BaseMidiButton* button) {
											  if (_editMode) {
												  _propertyWidget->targetButton(button);
											  }
										  });
				});
		selectLayout->addWidget(showKeyboardLayout);
		keyboardLayout->addLayout(selectLayout);
	}

	_propertyWidget = new MidiProperty;
	_propertyWidget->setVisible(false);

	auto editMode = new QCheckBox("Edit mode");
	connect(editMode,
			&QCheckBox::stateChanged,
			[this](bool state) {
				_editMode = state;
				_propertyWidget->setVisible(_editMode);
			});
	keyboardLayout->addWidget(editMode);
	mainLayout->addLayout(keyboardLayout);

	mainLayout->addWidget(_propertyWidget);
}

#pragma region Callbacks

#pragma endregion Callbacks
