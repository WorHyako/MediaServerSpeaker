#pragma once

#include <QMainWindow>

namespace Mss::Gui::Dialogs {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class MainWindow
			: public QMainWindow {
		Q_OBJECT

	public:
		/**
		 * @brief
		 *
		 * @param parent
		 */
		explicit MainWindow(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~MainWindow() override = default;

#pragma region Callbacks
    signals:

        /**
         * @brief
         *
         * @param value
         */
        void editModeChanged(bool value);

#pragma endregion Callbacks

    };
}
