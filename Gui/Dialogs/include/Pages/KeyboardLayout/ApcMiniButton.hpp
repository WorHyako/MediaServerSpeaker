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
		 * @brief	Ctor.
		 *
		 * @param	buttonText
		 *
		 * @param	parent		Parent widget.
		 */
		explicit ApcMiniButton(const QString &buttonText = "", QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ApcMiniButton() noexcept override = default;
	};
}
