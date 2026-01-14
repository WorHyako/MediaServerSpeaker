module;

#include "Wor/Midi/CallbackInfo/ApcMiniLed.hpp"

export module mss.backend:midi.MidiRoad;

namespace Mss::Backend::Midi {
/**
 * @brief Object to control midi launchpad signals.
 *
 * Controls active/passive status of launchpad's midi button.
 * Store roads in road map object.
 *
 * @usage
 * @code
 *     MidiRoad road;
 *     road.activeLed(led1);
 *     road.defaultLed(led2);
 *     road.go();
 * @endcode
 *
 * @see MidiRoadMap
 *
 * @author WorHyako
 */
export class MidiRoad final {
  public:
    /**
     * @brief Constructor.
     *
     * @param button_id Midi button id.
     */
    explicit MidiRoad(std::uint8_t button_id) noexcept;

    /**
     * @brief Sends out message to launchpad if it's possible.
     *
     * Changes active status via internal class field.
     */
    void go() noexcept;

  private:
    /**
     * @brief Midi button's id.
     */
    std::uint8_t button_id_;

    /**
     * @brief Current state of midi button.
     */
    bool is_active_;

    /**
     * @brief Led when button is active.
     */
    Wor::Midi::CallbackInfo::MidiLed active_led_;

    /**
     * @brief Led when button is passive.
     */
    Wor::Midi::CallbackInfo::MidiLed default_led_;

  public:
#pragma region Accessors / Mutators
    /**
     * @brief Returns the active led.
     *
     * @return Active led.
     */
    [[nodiscard]]
    Wor::Midi::CallbackInfo::MidiLed get_active_led() const noexcept;

    /**
     * @brief Returns the default led.
     *
     * @return Default led.
     */
    [[nodiscard]]
    Wor::Midi::CallbackInfo::MidiLed get_default_led() const noexcept;

    /**
     * @brief Sets the active led.
     *
     * @param led New led.
     */
    void set_active_led(const Wor::Midi::CallbackInfo::MidiLed &led) noexcept;

    /**
     * @brief Sets the default led.
     *
     * @param led New led.
     */
    void set_default_led(const Wor::Midi::CallbackInfo::MidiLed &led) noexcept;

#pragma endregion Accessors / Mutators
};
}
