#pragma once

#include <QWidget>

class QTextEdit;

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

		QTextEdit* _userNameText;

		QTextEdit* _userPasswordText;

		QTextEdit* _hostText;

		QTextEdit* _portText;

		QTextEdit* _dbNameText;

	public:
#pragma region Accessors/Mutators

#pragma endregion Accessors/Mutators
	};
}
