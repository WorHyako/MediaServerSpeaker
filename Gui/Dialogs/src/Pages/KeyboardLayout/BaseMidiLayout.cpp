#include "Pages/KeyboardLayout/BaseMidiLayout.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

BaseMidiLayout::BaseMidiLayout(QWidget *parent) noexcept
	: QWidget(parent) {
}

#pragma region Accessors/Mutators

const std::vector<BaseMidiButton *> &BaseMidiLayout::midiButtons() const noexcept {
	return _midiButtons;
}

#pragma endregion Accessors/Mutators
