#pragma once

#include "BaseMidiButton.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

/**
 * @brief Button widget for APC Mini MIDI controller.
 *
 * @author WorHyako
 */
class ApcMiniButton : public BaseMidiButton {
  public:
    /**
     * @brief Constructor.
     *
     * @param button_text Text displayed on the button.
     * @param parent Parent widget.
     */
    explicit ApcMiniButton(const QString &button_text = "", QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~ApcMiniButton() noexcept override = default;
};
}
