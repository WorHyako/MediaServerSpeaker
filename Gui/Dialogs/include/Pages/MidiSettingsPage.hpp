#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
class BaseMidiLayout;
}

namespace Mss::Gui::Dialogs::Pages {
class MidiProperty;
}

namespace Mss::Gui::Dialogs::Pages {
/**
 * @brief MIDI settings page widget.
 *
 * @author WorHyako
 */
class MidiSettingsPage : public QWidget {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit MidiSettingsPage(QWidget *parent = nullptr) noexcept;

  private:
    /**
     * @brief Saves the current MIDI settings.
     */
    void save() const noexcept;

    /**
     * @brief Loads the MIDI settings from storage.
     */
    void load() noexcept;

    KeyboardLayout::BaseMidiLayout *keyboard_layout_widget_;

    MidiProperty *property_widget_;

    bool edit_mode_;

#pragma region Callbacks

  public slots:
    /**
     * @brief Slot called when a MIDI key is pressed.
     */
    void midi_key_pressed();

#pragma endregion Callbacks
};
}
