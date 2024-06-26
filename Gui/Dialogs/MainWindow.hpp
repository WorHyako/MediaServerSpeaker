#pragma once

#include <QMainWindow>

class QGridLayout;

namespace MSS::Gui::Dialogs {

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
        explicit MainWindow(QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~MainWindow() override = default;

    private:
        QGridLayout *_mainLayout;
    };
}
