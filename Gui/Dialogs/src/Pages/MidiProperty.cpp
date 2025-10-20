#include "Pages/MidiProperty.hpp"

#include "Midi/MidiRoadMap.hpp"

#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

#include "Wor/Midi/CallbackInfo/ApcMiniLed.hpp"
#include "Wor/Wrappers/Singleton.hpp"

using namespace Mss::Gui::Dialogs::Pages;

MidiProperty::MidiProperty(QWidget *parent) noexcept
    : QWidget{ parent } {
    auto properties_layout{ new QVBoxLayout };
    QWidget::setLayout(properties_layout);

    auto title_label{ new QLabel("Properties") };
    properties_layout->addWidget(title_label);
    {
        auto layout{ new QHBoxLayout };
        const auto label{ new QLabel("Id:") };
        layout->addWidget(label);
        id_text_ = new QTextEdit;
        id_text_->setFixedHeight(30);
        id_text_->setEnabled(false);
        layout->addWidget(id_text_);
        properties_layout->addLayout(layout);
    }
    {
        auto layout{ new QHBoxLayout };
        const auto label{ new QLabel("Active color:") };
        layout->addWidget(label);
        active_color_combo_box_ = new QComboBox;
        layout->addWidget(active_color_combo_box_);
        properties_layout->addLayout(layout);
    }
    {
        auto layout{ new QHBoxLayout };
        const auto label{ new QLabel("Default color:") };
        layout->addWidget(label);
        default_color_combo_box_ = new QComboBox;
        layout->addWidget(default_color_combo_box_);
        properties_layout->addLayout(layout);
    }
}

#pragma region Accessors / Mutators

void MidiProperty::target_midi_idx(std::uint8_t button_idx) noexcept {
    id_text_->setText(QString::number(button_idx));

    auto &roadMap{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
    auto road{ roadMap.midi_road(button_idx).value() };

    active_color_combo_box_->clear();
    std::ignore = active_color_combo_box_->disconnect();

    default_color_combo_box_->clear();
    std::ignore = default_color_combo_box_->disconnect();

    const auto colors{ Wor::Midi::CallbackInfo::ApcMini::ApcMiniLed::availableLeds() };

    std::ranges::for_each(
        colors,
        [&color_combobox{ active_color_combo_box_ }](const Wor::Midi::CallbackInfo::MidiLed &color) {
            const auto item_text{ std::format("{} {}", color.colorName(), color.modeName()) };
            color_combobox->addItem(item_text.c_str());
        }
    );
    const auto current_active_color_it{ std::ranges::find_if(colors,
                                                             [road](const Wor::Midi::CallbackInfo::MidiLed &each) {
                                                                 return each == road.get_active_led();
                                                             }) };
    const auto activeColorIdx{ std::distance(std::begin(colors), current_active_color_it) };
    active_color_combo_box_->setCurrentIndex(activeColorIdx);

    std::ranges::for_each(
        colors,
        [&color_combobox{ default_color_combo_box_ }](const Wor::Midi::CallbackInfo::MidiLed &color) {
            const auto item_text{ std::format("{} {}", color.colorName(), color.modeName()) };
            color_combobox->addItem(item_text.c_str());
        }
    );
    const auto current_default_color_it{ std::ranges::find_if(colors,
                                                              [road](const Wor::Midi::CallbackInfo::MidiLed &each) {
                                                                  return each == road.get_default_led();
                                                              }) };
    const auto defaultColorIdx{ std::distance(std::begin(colors), current_default_color_it) };
    default_color_combo_box_->setCurrentIndex(defaultColorIdx);

    std::ignore = connect(
        active_color_combo_box_,
        &QComboBox::currentIndexChanged,
        [roadMap, roadIdx{ button_idx }, colors](int idx) {
            if (idx == -1) {
                return;
            }
            auto current_road{ roadMap.midi_road(roadIdx).value() };
            current_road.set_active_led(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
        }
    );

    std::ignore = connect(
        default_color_combo_box_,
        &QComboBox::currentIndexChanged,
        [roadMap, road_idx{ button_idx }, colors](int idx) {
            if (idx == -1) {
                return;
            }
            auto current_road{ roadMap.midi_road(road_idx).value() };
            current_road.set_default_led(static_cast<Wor::Midi::CallbackInfo::MidiLed>(colors[idx]));
        }
    );
}

#pragma endregion Accessors / Mutators
