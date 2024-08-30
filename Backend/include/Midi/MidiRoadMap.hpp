#pragma once

#include "ServerRoad.hpp"
#include "MidiRoad.hpp"

#include "Midi/CallbackInfo/BaseCallbackInfo.hpp"

#include <unordered_map>

namespace Mss::Backend::Midi {
	/**
	 * @brief
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
		 * @brief
		 *
		 * @param midiKeyIdx
		 *
		 * @param road
		 */
		void addRoad(std::uint8_t midiKeyIdx, MidiRoad road) noexcept;

		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 *
		 * @param road
		 */
		void addRoad(std::uint8_t midiKeyIdx, ServerRoad road) noexcept;

		/**
		 * @brief
		 *
		 * @param callbackInfo
		 */
		void transmit(const Wor::Midi::CallbackInfo::BaseCallbackInfo &callbackInfo) noexcept;

		/**
		 * @brief
		 */
		void clear() noexcept;

		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void removeRoad(std::uint8_t midiKeyIdx) noexcept;

		/**
		 * @brief
		 */
		void save() const noexcept;

		/**
		 * @brief
		 */
		void load() noexcept;

	private:
		std::unordered_map<std::uint8_t, ServerRoad> _serverRoad;

		std::unordered_map<std::uint8_t, MidiRoad> _midiRoad;

		std::uint8_t _buttonIdIdx;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param idx
		 */
		void buttonIdIdx(std::uint8_t idx) noexcept;

#pragma endregion Accessors/Mutators
	};
}
