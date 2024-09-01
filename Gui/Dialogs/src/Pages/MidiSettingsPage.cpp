#include "Pages/MidiSettingsPage.hpp"

#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMouseEvent>

#include "Midi/MidiRoad.hpp"
#include "Midi/MidiRoadMap.hpp"
#include "Config/Config.hpp"
#include "Pages/KeyboardLayout/ApcMini.hpp"
#include "Pages/MidiProperty.hpp"

#include "Wor/Midi/MidiDeviceList.hpp"
#include "Wor/Wrappers/Singleton.hpp"

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
		std::ignore = connect(showKeyboardLayout,
							  &QPushButton::clicked,
							  [devices, comboBox,keyboardLayout, this]() {
								  auto activeIdx = comboBox->currentIndex();
								  if (activeIdx == -1) {
									  return;
								  }
								  const auto &deviceName = devices[activeIdx];

								  if (_keyboardLayoutWidget != nullptr) {
									  layout()->removeWidget(_keyboardLayoutWidget);
									  _keyboardLayoutWidget->deleteLater();
								  }
								  /**
								   * TODO: Implement enum casting
								   */
								  if (deviceName == "APC MINI") {
									  auto &roadMap = Wor::Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
									  roadMap.buttonIdIdx(1);
									  _keyboardLayoutWidget = new KeyboardLayout::ApcMini;
									  keyboardLayout->addWidget(_keyboardLayoutWidget);
								  }

								  std::ignore = connect(_keyboardLayoutWidget,
														&KeyboardLayout::BaseMidiLayout::midiKeyPressed,
														[this](std::uint8_t midiIdx) {
															if (_editMode) {
																_propertyWidget->targetMidiIdx(midiIdx);
															}
														});
							  });
		selectLayout->addWidget(showKeyboardLayout);
		keyboardLayout->addLayout(selectLayout);
	}

	_propertyWidget = new MidiProperty;
	_propertyWidget->setVisible(false);

	auto editMode = new QCheckBox("Edit mode");
	std::ignore = connect(editMode,
						  &QCheckBox::stateChanged,
						  [this](bool state) {
							  _editMode = state;
							  _propertyWidget->setVisible(_editMode);
						  });
	keyboardLayout->addWidget(editMode);
	mainLayout->addLayout(keyboardLayout);

	mainLayout->addWidget(_propertyWidget);

	{
		auto layout = new QHBoxLayout;
		auto save = new QPushButton("Save");
		std::ignore = connect(save,
							  &QPushButton::clicked,
							  [this]() {
								  this->save();
							  });
		layout->addWidget(save);

		auto load = new QPushButton("Load");
		std::ignore = connect(load,
							  &QPushButton::clicked,
							  [this]() {
								  this->load();
							  });
		layout->addWidget(load);
		mainLayout->addLayout(layout);
	}
}

void MidiSettingsPage::save() const noexcept {
	if (!_keyboardLayoutWidget) {
		return;
	}

	auto midiButtons = _keyboardLayoutWidget->midiButtons();
	auto &roadMap = Wor::Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
	std::ranges::for_each(midiButtons,
						  [&roadMap](auto &button) {
							  Backend::Midi::MidiRoad road(button->midiKeyIdx());
							  road.activeLed(button->activeColor());
							  road.defaultLed(button->defaultColor());
							  roadMap.addRoad(button->midiKeyIdx(), road);
						  });
	roadMap.save();
}

void MidiSettingsPage::load() noexcept {
	auto &roadMap = Wor::Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
	roadMap.load();
}

#pragma region Callbacks

#pragma endregion Callbacks
