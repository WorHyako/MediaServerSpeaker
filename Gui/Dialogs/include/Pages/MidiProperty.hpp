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
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit MidiProperty(QWidget *parent = nullptr) noexcept;

	private:
		QComboBox *_activeColorComboBox;

		QComboBox *_defaultColorComboBox;

		QTextEdit *_idText;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param idx
		 */
		void targetMidiIdx(std::uint8_t idx) noexcept;

#pragma endregion Accessors/Mutators
	};
}
