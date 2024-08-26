#pragma once

#include "IMidiButton.hpp"

#include "Midi/CallbackInfo/ApcMiniInCallbackInfo.hpp"
#include "Midi/CallbackInfo/ApcMiniOutCallbackInfo.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ApcMiniButton
			: public IMidiButton {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param buttonText
		 *
		 * @param parent
		 */
		explicit ApcButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ApcButton() noexcept override = default;

	private:
		std::uint8_t _color;

		std::uint8_t _colorType;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept;

		/**
		 * @brief
		 *
		 * @param color
		 */
		void color(std::uint16_t color) noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::string colorRgbStr() noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t colorType() noexcept override;

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
