#include "Pages/MidiSettingsPage.hpp"

#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

#include "Config/Config.hpp"
#include "Pages/KeyboardLayout/AkaiApcMini.hpp"

#include "Midi/MidiDeviceList.hpp"

using namespace Mss::Gui::Dialogs::Pages;

MidiSettingsPage::MidiSettingsPage(QWidget *parent) noexcept
	: QWidget(parent),
	  _keyboardLayoutWidget(new QWidget),
	  _editMode(false) {
	auto vLayout = new QVBoxLayout;
	QWidget::setLayout(vLayout);

	auto hLayout = new QHBoxLayout;

	auto midiKeyboardLabel = new QLabel("Keyboards:");
	hLayout->addWidget(midiKeyboardLabel);

	auto comboBox = new QComboBox;

	auto devices = Wor::Midi::MidiDeviceList::getKeyboards();
	std::for_each(std::begin(devices),
				  std::end(devices),
				  [comboBox](const std::string &device) {
					  comboBox->addItem(device.c_str());
				  });

	hLayout->addWidget(comboBox);

	auto showKeyboardLayout = new QPushButton("Show");
	connect(showKeyboardLayout,
			&QPushButton::clicked,
			[devices, comboBox, this]() {
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
					_keyboardLayoutWidget = new KeyboardLayout::AkaiApcMini;
					layout()->addWidget(_keyboardLayoutWidget);
				}
			});
	hLayout->addWidget(showKeyboardLayout);

	vLayout->addLayout(hLayout);

	auto editMode = new QCheckBox("Edit mode");
	connect(editMode,
			&QCheckBox::stateChanged,
			[this](bool state) {
				_editMode = state;
			});
	vLayout->addWidget(editMode);
}
