#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	class BaseMidiLayout;
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
		/**
		 * @brief
		 */
		void save() const noexcept;

		/**
		 * @brief
		 */
		void load() noexcept;

		KeyboardLayout::BaseMidiLayout *_keyboardLayoutWidget;

		MidiProperty *_propertyWidget;

		bool _editMode;

#pragma region Callbacks

	public slots:
		/**
		 * @brief
		 */
		void midiKeyPressed();

#pragma endregion Callbacks
	};
}
