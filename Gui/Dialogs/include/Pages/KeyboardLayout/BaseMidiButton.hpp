#pragma once

#include <QPushButton>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class BaseMidiButton
			: public QPushButton {
	public:
		using ColorValue = std::pair<std::uint8_t, std::uint8_t>;

		/**
		 * @brief
		 *
		 * @param buttonText
		 *
		 * @param parent
		 */
		explicit BaseMidiButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~BaseMidiButton() noexcept override = default;

	protected:
		std::uint8_t _midiKeyIdx;

		ColorValue _activeColor;

		ColorValue _defaultColor;

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
		virtual void activeColor(ColorValue color) noexcept;

		/**
		 * @brief
		 *
		 * @param color
		 */
		virtual void defaultColor(ColorValue color) noexcept;

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
		virtual ColorValue activeColor() const noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual ColorValue defaultColor() const noexcept;

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
