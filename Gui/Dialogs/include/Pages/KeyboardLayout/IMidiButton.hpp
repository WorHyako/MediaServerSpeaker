#pragma once

#include <QPushButton>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class IMidiButton
			: public QPushButton {
	public:
		/**
		 * @brief
		 *
		 * @param buttonText
		 *
		 * @param parent
		 */
		explicit IMidiButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~IMidiButton() noexcept override = default;

	protected:
		std::uint8_t _midiKeyIdx;

		std::uint8_t _activeColor;

		std::uint8_t _defaultColor;

		std::uint8_t _colorMode;

		bool _isActive;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		virtual void midiKeyIdx(std::uint8_t midiKeyIdx) noexcept = 0;

		/**
		 * @brief
		 *
		 * @param color
		 */
		virtual void activeColor(std::uint8_t color) noexcept = 0;

		/**
		 * @brief
		 *
		 * @param color
		 */
		virtual void defaultColor(std::uint8_t color) noexcept = 0;

		/**
		 * @brief
		 *
		 * @param colorMode
		 */
		virtual void colorMode(std::uint8_t colorMode) noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::string colorRgbStr() const noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::uint8_t colorMode() const noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::uint8_t activeColor() const noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::uint8_t defaultColor() const noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::uint8_t midiKeyIdx() const noexcept = 0;

#pragma endregion Accessors/Mutators

	};
}
