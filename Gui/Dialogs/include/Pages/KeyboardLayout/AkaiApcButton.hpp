#pragma once

#include <QPushButton>

#include "Midi/CallbackInfo/AkaiApcInCallbackInfo.hpp"
#include "Midi/CallbackInfo/AkaiApcOutCallbackInfo.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class AkaiApcButton
			: public QPushButton {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param buttonText
		 *
		 * @param parent
		 */
		explicit AkaiApcButton(const QString &buttonText, QWidget *parent = nullptr) noexcept;

	private:
		std::uint8_t _midiKeyIdx;

		std::uint8_t _color;

#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

		/**
		 * @brief
		 *
		 * @param event
		 */
		void mousePressEvent(QMouseEvent *event) noexcept override;

#pragma endregion Callbacks
	};
}
