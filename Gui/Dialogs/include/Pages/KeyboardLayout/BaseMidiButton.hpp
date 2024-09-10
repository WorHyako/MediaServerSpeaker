#pragma once

#include <QPushButton>

#include "Wor/Midi/CallbackInfo/MidiLed.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class BaseMidiButton
			: public QPushButton {
		using MidiLed = Wor::Midi::CallbackInfo::MidiLed;
	public:
		/**
		 * @brief
		 *
		 * @param	buttonText
		 *
		 * @param	parent		Parent widget.
		 */
		explicit BaseMidiButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~BaseMidiButton() noexcept override = default;

	protected:
		std::uint8_t _midiKeyIdx;

		MidiLed _activeColor;

		MidiLed _defaultColor;

		bool _isActive;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		virtual void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept;

		/**
		 * @brief
		 *
		 * @param color
		 */
		virtual void activeColor(MidiLed color) noexcept;

		/**
		 * @brief
		 *
		 * @param color
		 */
		virtual void defaultColor(MidiLed color) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual MidiLed activeColor() const noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual MidiLed defaultColor() const noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::uint8_t midiKeyIdx() const noexcept;

#pragma endregion Accessors/Mutators

	};
}
