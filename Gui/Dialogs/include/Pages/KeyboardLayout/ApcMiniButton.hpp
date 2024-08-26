#pragma once

#include "IMidiButton.hpp"

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
		explicit ApcMiniButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ApcMiniButton() noexcept override = default;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t midiKeyIdx() const noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t activeColor() const noexcept override;

		/**
		 * @brief
		 *
		 * @param color
		 */
		void activeColor(std::uint8_t color) noexcept override;

		/**
		 * @brief
		 *
		 * @param color
		 */
		void defaultColor(std::uint8_t color) noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t defaultColor() const noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::uint8_t colorMode() const noexcept override;

		/**
		 * @brief
		 *
		 * @param colorMode
		 */
		void colorMode(std::uint8_t colorMode) noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::string colorRgbStr() const noexcept override;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

		/**
		 * @brief
		 *
		 * @param e
		 */
		void mousePressEvent(QMouseEvent *e) noexcept override;

#pragma endregion Callbacks
	};
}
