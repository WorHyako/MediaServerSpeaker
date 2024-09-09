#pragma once

#include <QWidget>

class QLineEdit;

namespace Mss::Gui::Dialogs::Pages {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class SqlSettingsPage
			: public QWidget {
	public:
		/**
		 * @brief Ctor
		 *
		 * @param parent
		 */
		explicit SqlSettingsPage(QWidget *parent = nullptr) noexcept;

	private:
		/**
		 * @brief
		 */
		void refreshSqlStatus() noexcept;

		QLineEdit* _userNameText;

		QLineEdit* _userPasswordText;

		QLineEdit* _hostText;

		QLineEdit* _portText;

		QLineEdit* _dbNameText;
	};
}
