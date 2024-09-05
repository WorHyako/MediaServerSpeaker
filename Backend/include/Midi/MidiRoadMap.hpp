#pragma once

#include "ServerRoad.hpp"
#include "MidiRoad.hpp"

#include "Wor/Midi/CallbackInfo/BaseCallbackInfo.hpp"

#include <unordered_map>

namespace Mss::Backend::Midi {
	/**
	 * @brief	Object to store and control all roads.
	 *			<p>
	 *			Recommend to use only as Singleton object.
	 *
	 * @usage
	 * @code
	 *			auto &roadMap = Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get();
	 *			roadMap.load();
	 *			auto road = roadMap.midiRoad(midiButtonIndex);
	 * @endcode
	 *
	 * @author WorHyako
	 */
	class MidiRoadMap {
	public:
		/**
		 * @brief Ctor.
		 */
		MidiRoadMap() noexcept;

		/**
		 * @brief Dtor.
		 */
		virtual ~MidiRoadMap() noexcept = default;

		/**
		 * @brief	Adds new road or overwrite existing one.
		 *
		 * @param	midiKeyIdx	Midi button id. It will be uses as road's index.
		 *
		 * @param	road		New road
		 */
		void addRoad(std::uint8_t midiKeyIdx, MidiRoad road) noexcept;

		/**
		 * @brief	Adds new road or overwrite existing one.
		*
		 * @param	midiKeyIdx	Midi button id. It will be uses as road's index.
		 *
		 * @param	road		New road
		 */
		void addRoad(std::uint8_t midiKeyIdx, ServerRoad road) noexcept;

		/**
		 * @brief	Transmits incoming callbacks to road map and transfer in to roads.
		 *
		 * @usage
		 * @code
		 * 			auto &roadMap = Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
		 *			midi.inCallback([&roadMap](Midi::CallbackInfo::BaseCallbackInfo callbackInfo) {
		 *				roadMap.transmit(callbackInfo);
		 *			});
		 * @endcode
		 *
		 * @param	callbackInfo
		 */
		void transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &callbackInfo) noexcept;

		/**
		 * @brief	Delete all roads from storage.
		 */
		void clear() noexcept;

		/**
		 * @brief	Remove midi and server road by index.
		 *
		 * @param	midiKeyIdx Road index.
		 */
		void removeRoad(std::uint8_t midiKeyIdx) noexcept;

		/**
		 * @brief	Save current midi and server roads to json file.
		 *			<p>
		 *			File path - "Resources/RoadMap/midi.json"
		 */
		void save() const noexcept;

		/**
		 * @brief	Load midi and server roads from json file.
		 *			<p>
		 *			File path - "Resources/RoadMap/midi.json"
		 */
		void load() noexcept;

	private:
		/**
		 * @brief Stores server roads. Midi button index uses as key.
		 */
		std::unordered_map<std::uint8_t, ServerRoad> _serverRoad;

		/**
		 * @brief Stores midi roads. Midi button index uses as key.
		 */
		std::unordered_map<std::uint8_t, MidiRoad> _midiRoad;

		/**
		 * @brief	Road id corresponds to midi button id.
		 *			<p>
		 *			Uses as index of road maps.
		 */
		std::uint8_t _buttonIdIdx;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Midi button id accessor.
		 *
		 * @param	idx Midi button id.
		 */
		void buttonIdIdx(std::uint8_t idx) noexcept;

		/**
		 * @brief	Midi road accessor.
		 *
		 * @param	midiIdx	Midi button id.
		 *
		 * @return	Midi road if it's exists.
		 */
		[[nodiscard]]
		std::optional<MidiRoad> midiRoad(std::uint8_t midiIdx) const noexcept;

		/**
		 * @brief	Server road accessor.
		 *
		 * @param	midiIdx	Midi button id.
		 *
		 * @return	Server road if it's exists.
		 */
		[[nodiscard]]
		std::optional<ServerRoad> serverRoad(std::uint8_t midiIdx) const noexcept;

#pragma endregion Accessors/Mutators
	};
}
