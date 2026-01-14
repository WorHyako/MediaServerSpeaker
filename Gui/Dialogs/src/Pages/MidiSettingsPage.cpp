#include "Pages/MidiSettingsPage.hpp"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>

#include "Wor/Midi/MidiDeviceList.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include "Config/Config.hpp"
#include "Pages/KeyboardLayout/ApcMini.hpp"
#include "Pages/MidiProperty.hpp"

import mss.backend;

using namespace Mss::Gui::Dialogs::Pages;

MidiSettingsPage::MidiSettingsPage(QWidget *parent) noexcept
    : QWidget{ parent },
      keyboard_layout_widget_{ nullptr },
      edit_mode_{ false } {
    auto main_layout{ new QHBoxLayout };
    QWidget::setLayout(main_layout);

    auto keyboard_layout{ new QVBoxLayout };
    {
        auto select_layout{ new QHBoxLayout };
        const auto midi_keyboard_label{ new QLabel("Keyboards:") };
        select_layout->addWidget(midi_keyboard_label);

        auto combo_box{ new QComboBox };

        auto devices{ Wor::Midi::MidiDeviceList::getKeyboards() };
        std::ranges::for_each(devices, [combo_box](const std::string_view &device) {
            combo_box->addItem(device.data());
        });

        select_layout->addWidget(combo_box);

        auto show_keyboard_layout{ new QPushButton("Show") };
        std::ignore =
            connect(show_keyboard_layout, &QPushButton::clicked, [devices, combo_box, keyboard_layout, this]() {
                const auto active_idx{ combo_box->currentIndex() };
                if (active_idx == -1) {
                    return;
                }
                const auto &device_name{ devices[active_idx] };

                if (keyboard_layout_widget_ != nullptr) {
                    layout()->removeWidget(keyboard_layout_widget_);
                    keyboard_layout_widget_->deleteLater();
                }
                /**
                 * TODO: Implement enum casting
                 */
                if (device_name == "APC MINI") {
                    auto &road_map{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
                    road_map.set_button_id_idx(1);
                    keyboard_layout_widget_ = new KeyboardLayout::ApcMini;
                    keyboard_layout->addWidget(keyboard_layout_widget_);
                }

                std::ignore = connect(
                    keyboard_layout_widget_,
                    &KeyboardLayout::BaseMidiLayout::midi_key_pressed,
                    [this](std::uint8_t midi_idx) {
                        if (edit_mode_) {
                            property_widget_->target_midi_idx(midi_idx);
                        }
                    }
                );
            });
        select_layout->addWidget(show_keyboard_layout);
        keyboard_layout->addLayout(select_layout);
    }

    property_widget_ = new MidiProperty;
    property_widget_->setVisible(false);

    auto edit_mode{ new QCheckBox("Edit mode") };
    std::ignore = connect(edit_mode, &QCheckBox::checkStateChanged, [this](bool state) {
        edit_mode_ = state;
        property_widget_->setVisible(edit_mode_);
    });
    keyboard_layout->addWidget(edit_mode);
    main_layout->addLayout(keyboard_layout);

    main_layout->addWidget(property_widget_);

    {
        auto layout{ new QHBoxLayout };
        auto save{ new QPushButton("Save") };
        std::ignore = connect(save, &QPushButton::clicked, [this]() {
            this->save();
        });
        layout->addWidget(save);

        auto load{ new QPushButton("Load") };
        std::ignore = connect(load, &QPushButton::clicked, [this]() {
            this->load();
        });
        layout->addWidget(load);
        main_layout->addLayout(layout);
    }
}

void MidiSettingsPage::save() const noexcept {
    if (!keyboard_layout_widget_) {
        return;
    }

    auto midi_buttons{ keyboard_layout_widget_->midi_buttons() };
    auto &road_map{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
    std::ranges::for_each(midi_buttons, [&road_map](auto &button) {
        Backend::Midi::MidiRoad road(button->get_midi_key_idx());
        road.set_active_led(button->get_active_color());
        road.set_default_led(button->get_default_color());
        road_map.add_road(button->get_midi_key_idx(), road);
    });
    road_map.save();
}

void MidiSettingsPage::load() noexcept {
    auto &roadMap{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
    roadMap.load();
}
