#include "Pages/KeyboardLayout/ApcMini.hpp"

#include "Pages/KeyboardLayout/ApcMiniButton.hpp"

#include <QGridLayout>

import worlib.midi;

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;
using namespace Wor::Midi;

namespace {
/**
 * @brief
 *
 * @param idx
 *
 * @return
 *
 * @author WorHyako
 */
std::pair<std::uint8_t, std::uint8_t> position_at_idx(std::uint8_t idx) {
    return { 7 - idx / 8, idx % 8 };
}
}

ApcMini::ApcMini(QWidget *parent) noexcept
    : BaseMidiLayout{ parent } {
    auto grid_layout{ new QGridLayout };
    QWidget::setLayout(grid_layout);

    for (auto row{ 0 }; row < 8; row++) {
        for (auto column{ 0 }; column < 8; column++) {
            auto button { new ApcMiniButton(QString::number(column + row * 8))};
            button->setAutoFillBackground(true);
            button->setStyleSheet("background-color: rgb(100, 100, 100);");
            grid_layout->addWidget(button, row, column);
        }
    }

    for (auto i { 0}; i < 64; i++) {
        const auto pos { ::position_at_idx(i)};
        const auto item { grid_layout->itemAtPosition(pos.first, pos.second)};
        auto button { reinterpret_cast<ApcMiniButton *>(item->widget())};
        midi_buttons_.emplace_back(button);
        button->setText(QString::number(i));
        std::ignore = connect(button, &ApcMiniButton::clicked, [this, i]() {
            emit midi_key_pressed(i);
        });
    }
}
