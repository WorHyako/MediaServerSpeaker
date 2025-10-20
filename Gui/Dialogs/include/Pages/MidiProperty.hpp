#pragma once

#include <QComboBox>
#include <QTextEdit>

#include "KeyboardLayout/ApcMiniButton.hpp"

namespace Mss::Gui::Dialogs::Pages {
/**
 * @brief Widget for displaying and editing MIDI button properties.
 *
 * @author WorHyako
 */
class MidiProperty : public QWidget {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit MidiProperty(QWidget *parent = nullptr) noexcept;

  private:
    QComboBox *active_color_combo_box_;

    QComboBox *default_color_combo_box_;

    QTextEdit *id_text_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the target MIDI button index.
     *
     * @param idx MIDI button index.
     */
    void target_midi_idx(std::uint8_t idx) noexcept;

#pragma endregion Accessors / Mutators
};
}
