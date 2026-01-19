#pragma once

#include <QPushButton>

import worlib.midi;

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
/**
 * @brief Base class for MIDI button widgets.
 *
 * @author WorHyako
 */
class BaseMidiButton : public QPushButton {
    using MidiLed = Wor::Midi::CallbackInfo::MidiLed;

  public:
    /**
     * @brief Constructor.
     *
     * @param button_text Text displayed on the button.
     * @param parent Parent widget.
     */
    explicit BaseMidiButton(const QString &button_text = "", QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~BaseMidiButton() noexcept override = default;

  protected:
    std::uint8_t midi_key_idx_;

    MidiLed active_color_;

    MidiLed default_color_;

    bool is_active_;

#pragma region Accessors / Mutators

  public:
    /**
     * @brief Sets the MIDI key index.
     *
     * @param midi_key_idx MIDI key index.
     */
    virtual void set_midi_key_idx(std::uint8_t midi_key_idx) noexcept;

    /**
     * @brief Sets the active color for the button.
     *
     * @param color Active color.
     */
    virtual void set_active_color(MidiLed color) noexcept;

    /**
     * @brief Sets the default color for the button.
     *
     * @param color Default color.
     */
    virtual void set_default_color(MidiLed color) noexcept;

    /**
     * @brief Returns the active color.
     *
     * @return Active color.
     */
    [[nodiscard]]
    virtual MidiLed get_active_color() const noexcept;

    /**
     * @brief Returns the default color.
     *
     * @return Default color.
     */
    [[nodiscard]]
    virtual MidiLed get_default_color() const noexcept;

    /**
     * @brief Returns the MIDI key index.
     *
     * @return MIDI key index.
     */
    [[nodiscard]]
    virtual std::uint8_t get_midi_key_idx() const noexcept;

#pragma endregion Accessors / Mutators
};
}
