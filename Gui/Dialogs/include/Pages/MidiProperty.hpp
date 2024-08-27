#pragma once

#include <QTextEdit>
#include <QComboBox>

#include "KeyboardLayout/ApcMiniButton.hpp"

namespace Mss::Gui::Dialogs::Pages {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class MidiProperty
			: public QWidget {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit MidiProperty(QWidget *parent = nullptr) noexcept;

	private:
		KeyboardLayout::ApcMiniButton *_button;

		QComboBox *_activeColorComboBox;

		QComboBox *_activeColorModeComboBox;

		QComboBox *_defaultColorComboBox;

		QComboBox *_defaultColorModeComboBox;

		QTextEdit *_idText;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param button
		 */
		void targetButton(KeyboardLayout::ApcMiniButton *button) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		KeyboardLayout::ApcMiniButton *targetButton() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
