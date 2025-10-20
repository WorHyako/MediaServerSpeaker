#pragma once

#include <cstdint>

namespace Mss::Gui::Components {
/**
 * @brief Object separates all operations with midi launchpad events.
 *
 * Designed for inheritance to add MIDI functionality to other classes.
 *
 * @usage
 * @code
 *     std::uint8_t midiKeyId = ...;
 *     MidiComponent::midiKeyId(midiKeyIdx);
 *     MidiComponent::goRoad();
 * @endcode
 *
 * @author WorHyako
 *
 * @see MidiRoad
 */
class MidiComponent {
  public:
    /**
     * @brief Constructor.
     */
    MidiComponent() noexcept;

    /**
     * @brief Destructor.
     */
    virtual ~MidiComponent() = default;

    /**
     * @brief Tries to execute midi road with current midi button id if it exists in road map.
     */
    void go_midi_road() noexcept;

  private:
    std::uint8_t midi_key_idx_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the MIDI button id.
     *
     * @param midi_button_id MIDI button id.
     */
    void set_midi_key_idx(std::uint8_t midi_button_id) noexcept;

    /**
     * @brief Returns the MIDI button id.
     *
     * @return MIDI button id.
     */
    [[nodiscard]]
    std::uint8_t get_midi_key_idx() const noexcept;

#pragma endregion Accessors / Mutators
};
}
