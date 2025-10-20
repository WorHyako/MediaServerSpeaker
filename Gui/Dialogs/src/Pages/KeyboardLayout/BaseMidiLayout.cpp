#include "Pages/KeyboardLayout/BaseMidiLayout.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiLayout::BaseMidiLayout(QWidget *parent) noexcept
    : QWidget{ parent } {
}

#pragma region Accessors / Mutators

const std::vector<BaseMidiButton *> &BaseMidiLayout::midi_buttons() const noexcept {
    return midi_buttons_;
}

#pragma endregion Accessors / Mutators
