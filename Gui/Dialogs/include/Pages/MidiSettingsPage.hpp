#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	class ApcMini;
}

namespace Mss::Gui::Dialogs::Pages {
	class MidiProperty;
}

namespace Mss::Gui::Dialogs::Pages {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class MidiSettingsPage
			: public QWidget {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit MidiSettingsPage(QWidget *parent = nullptr) noexcept;

	private:
		KeyboardLayout::ApcMini *_keyboardLayoutWidget;

		MidiProperty *_propertyWidget;

		bool _editMode;

#pragma region Callbacks

#pragma endregion Callbacks
	};
}
