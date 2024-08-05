#pragma once

#include <QMainWindow>

#include "Network/TcpServer.hpp"

class QGridLayout;

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

        /**
         * @brief
         */
        void startServer() noexcept;

    signals:

        /**
         * @brief
         *
         * @param value
         */
        void editModeChanged(bool value);

    private:

        std::unique_ptr<Wor::Network::TcpServer> _server;

    public:
#pragma region Accessors/Mutators

//        /**
//         * @brief
//         *
//         * @return
//         */
//        [[nodiscard]]
//        const Wor::Network::TcpServer *getServer() const noexcept;

#pragma endregion Accessors/Mutators
    };
}
