#include "Pages/MidiProperty.hpp"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

#include "Midi/MidiRoadMap.hpp"

#include "Wor/Midi/CallbackInfo/ApcMiniLed.hpp"
#include "Wor/TemplateWrapper/Singleton.hpp"

using namespace Mss::Gui::Dialogs::Pages;

MidiProperty::MidiProperty(QWidget *parent) noexcept
	: QWidget(parent) {
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

void MidiProperty::targetMidiIdx(std::uint8_t buttonIdx) noexcept {
	_idText->setText(QString::number(buttonIdx));

	auto &roadMap = Wor::TemplateWrapper::Singleton<Backend::Midi::MidiRoadMap>::get();
	auto road = roadMap.midiRoad(buttonIdx);

	_activeColorComboBox->clear();
	std::ignore = _activeColorComboBox->disconnect();

	_defaultColorComboBox->clear();
	std::ignore = _defaultColorComboBox->disconnect();

	auto colors = Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed::availableLeds();

	std::ranges::for_each(colors,
						  [&colorCombobox = _activeColorComboBox](
						  const Wor::Midi::CallbackInfo::MidiLed &color) {
							  auto itemText = std::format("{} {}", color.colorName(), color.modeName());
							  colorCombobox->addItem(itemText.c_str());
						  });
	auto currentActiveColorIt = std::ranges::find_if(colors,
													 [road](const Wor::Midi::CallbackInfo::MidiLed &each) {
														 return each == road.activeLed();
													 });
	std::uint8_t activeColorIdx = std::distance(std::begin(colors), currentActiveColorIt);
	_activeColorComboBox->setCurrentIndex(activeColorIdx);

	std::ranges::for_each(colors,
						  [&colorCombobox = _defaultColorComboBox](
						  const Wor::Midi::CallbackInfo::MidiLed &color) {
							  auto itemText = std::format("{} {}", color.colorName(), color.modeName());
							  colorCombobox->addItem(itemText.c_str());
						  });
	auto currentDefaultColorIt = std::ranges::find_if(colors,
													  [road](const Wor::Midi::CallbackInfo::MidiLed &each) {
														  return each == road.defaultLed();
													  });
	std::uint8_t defaultColorIdx = std::distance(std::begin(colors), currentDefaultColorIt);
	_defaultColorComboBox->setCurrentIndex(defaultColorIdx);

	std::ignore = connect(_activeColorComboBox,
						  &QComboBox::currentIndexChanged,
						  [roadMap, roadIdx = buttonIdx, colors](int idx) {
							  if (idx == -1) {
								  return;
							  }
							  auto currentRoad = roadMap.midiRoad(roadIdx);
							  currentRoad.activeLed(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
						  });

	std::ignore = connect(_defaultColorComboBox,
						  &QComboBox::currentIndexChanged,
						  [roadMap, roadIdx = buttonIdx, colors](int idx) {
							  if (idx == -1) {
								  return;
							  }
							  auto currentRoad = roadMap.midiRoad(roadIdx);
							  currentRoad.defaultLed(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
						  });
}

#pragma endregion Accessors/Mutators
