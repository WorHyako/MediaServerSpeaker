#include "MainWindow.hpp"

#include "Tabs/ControlTab.hpp"

#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent) noexcept
        : QMainWindow(parent) {
    QMainWindow::setWindowTitle("Media Server Speaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    auto tabs = new Scopes::ControlTab(this);
    QMainWindow::setCentralWidget(tabs);

    auto menuBar = QMainWindow::menuBar();

    auto settings = menuBar->addMenu(tr("&Settings"));

    settings->addSeparator();

    auto editMode = settings->addAction("Edit mode");
    editMode->setCheckable(true);
    connect(editMode, &QAction::toggled, [tabs](bool toggled) {
        emit
        tabs->editModeChanged(toggled);
    });


    auto wid = new QWidget(this);
    wid->resize(400, 400);

    auto hLayout = new QVBoxLayout;
    wid->setLayout(hLayout);
    auto textToClients = new QTextEdit("text", this);
    hLayout->addWidget(textToClients);

    auto temp = new QPushButton("Connect and text to server", this);
    connect(temp, &QPushButton::pressed, [this, textToClients]() {
        _server->sendToAll(textToClients->toPlainText().toStdString());
    });
    hLayout->addWidget(temp);
}

const Wor::Network::TcpServer *MainWindow::getServer() const noexcept {
    return _server.get();
}

void MainWindow::initServer(boost::asio::io_service& ioService, std::uint16_t port) noexcept {
    _server.reset(new Wor::Network::TcpServer(ioService, port));
    _server->start();
}
