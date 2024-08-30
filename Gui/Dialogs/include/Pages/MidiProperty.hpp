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
		KeyboardLayout::BaseMidiButton *_button;

		QComboBox *_activeColorComboBox;

		QComboBox *_defaultColorComboBox;

		QTextEdit *_idText;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param button
		 */
		void targetButton(KeyboardLayout::BaseMidiButton *button) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		KeyboardLayout::BaseMidiButton *targetButton() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
