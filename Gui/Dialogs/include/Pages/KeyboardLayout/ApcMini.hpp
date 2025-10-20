#pragma once

#include "Pages/KeyboardLayout/BaseMidiLayout.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
/**
 * @brief APC Mini MIDI controller layout widget.
 *
 * @author WorHyako
 */
class ApcMini : public BaseMidiLayout {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit ApcMini(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~ApcMini() noexcept override = default;
};
}
