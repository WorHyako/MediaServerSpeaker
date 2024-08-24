#pragma once

#include <QWidget>

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
		QWidget* _keyboardLayoutWidget;

		bool _editMode;
	};
}
