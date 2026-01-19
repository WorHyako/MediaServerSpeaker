module;

export module mss.backend:midi.MidiRoadMap;
import :midi.MidiRoad;
import :midi.ServerRoad;

import worlib.midi;

import std;

namespace Mss::Backend::Midi {
/**
 * @brief Object to store and control all roads.
 *
 * Recommend using only as a Singleton object.
 *
 * @usage
 * @code
 *     auto &roadMap = Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get();
 *     roadMap.load();
 *     auto road = roadMap.midiRoad(midiButtonIndex);
 * @endcode
 *
 * @author WorHyako
 */
export class MidiRoadMap {
  public:
    /**
     * @brief Constructor.
     */
    MidiRoadMap() noexcept;

    /**
     * @brief Destructor.
     */
    virtual ~MidiRoadMap() noexcept = default;

    /**
     * @brief Adds new road or overwrites existing one.
     *
     * @param midi_key_idx Midi button id. It will be used as road's index.
     * @param road New road.
     */
    void add_road(std::uint8_t midi_key_idx, MidiRoad road) noexcept;

    /**
     * @brief Adds new road or overwrites existing one.
     *
     * @param midi_key_idx Midi button id. It will be used as road's index.
     * @param road New road.
     */
    void add_road(std::uint8_t midi_key_idx, ServerRoad road) noexcept;

    /**
     * @brief Transmits incoming callbacks to road map and transfers them to roads.
     *
     * @usage
     * @code
     *     auto &roadMap = Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
     *     midi.inCallback([&roadMap](Midi::CallbackInfo::BaseCallbackInfo callbackInfo) {
     *         roadMap.transmit(callbackInfo);
     *     });
     * @endcode
     *
     * @param callback_info Callback information.
     */
    void transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &callback_info) noexcept;

    /**
     * @brief Deletes all roads from storage.
     */
    void clear() noexcept;

    /**
     * @brief Removes midi and server road by index.
     *
     * @param midi_key_idx Road index.
     */
    void remove_road(std::uint8_t midi_key_idx) noexcept;

    /**
     * @brief Saves current midi and server roads to json file.
     *
     * File path - "Resources/RoadMap/midi.json"
     */
    void save() const noexcept;

    /**
     * @brief Loads midi and server roads from json file.
     *
     * File path - "Resources/RoadMap/midi.json"
     */
    void load() noexcept;

  private:
    /**
     * @brief Stores server roads. Midi button index is used as key.
     */
    std::unordered_map<std::uint8_t, ServerRoad> server_road_;

    /**
     * @brief Stores midi roads. Midi button index is used as key.
     */
    std::unordered_map<std::uint8_t, MidiRoad> midi_road_;

    /**
     * @brief Road id corresponds to midi button id.
     *
     * Used as index of road maps.
     */
    std::uint8_t button_id_idx_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the midi button id.
     *
     * @param idx Midi button id.
     */
    void set_button_id_idx(std::uint8_t idx) noexcept;

    /**
     * @brief Returns the midi road.
     *
     * @param midi_idx Midi button id.
     *
     * @return Midi road if it exists.
     */
    [[nodiscard]]
    std::optional<MidiRoad> midi_road(std::uint8_t midi_idx) const noexcept;

    /**
     * @brief Returns the server road.
     *
     * @param midi_idx Midi button id.
     *
     * @return Server road if it exists.
     */
    [[nodiscard]]
    std::optional<ServerRoad> server_road(std::uint8_t midi_idx) const noexcept;

#pragma endregion Accessors / Mutators
};
}
