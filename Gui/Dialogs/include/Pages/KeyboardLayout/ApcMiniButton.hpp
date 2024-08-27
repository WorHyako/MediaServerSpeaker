#pragma once

#include "BaseMidiButton.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ApcMiniButton
			: public BaseMidiButton {
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
