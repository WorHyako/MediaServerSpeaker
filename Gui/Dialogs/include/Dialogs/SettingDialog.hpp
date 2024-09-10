#pragma once

#include <QDialog>

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Dialogs {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class SettingDialog
			: public QDialog {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit SettingDialog(QWidget *parent = nullptr) noexcept;
	};
}
