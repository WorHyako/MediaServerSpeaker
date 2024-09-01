#pragma once

#include <QWidget>

class QPushButton;
class QVBoxLayout;

namespace Mss::Gui::Dialogs::Pages {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class NetworkSettingPage
			: public QWidget {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit NetworkSettingPage(QWidget *parent = nullptr) noexcept;

	private:
		/**
		 * @brief
		 */
		void refreshServerStatus() noexcept;

		QVBoxLayout *_sessionListLayout;

		QPushButton *_serverConnectButton;
	};

}
