#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
class BaseMidiButton;
}

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

/**
 * @brief Base class for MIDI controller layout widgets.
 *
 * @author WorHyako
 */
class BaseMidiLayout : public QWidget {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit BaseMidiLayout(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~BaseMidiLayout() noexcept override = default;

  protected:
    std::vector<BaseMidiButton *> midi_buttons_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Returns the list of MIDI buttons.
     *
     * @return Vector of MIDI buttons.
     */
    [[nodiscard]]
    const std::vector<BaseMidiButton *> &midi_buttons() const noexcept;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

  signals:
    /**
     * @brief Signal emitted when a MIDI key is pressed.
     *
     * @param idx MIDI key index.
     */
    void midi_key_pressed(std::uint8_t idx);

#pragma endregion Callbacks
};

}
