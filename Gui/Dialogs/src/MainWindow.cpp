#include "MainWindow.hpp"

#include "Tabs/ControlTab.hpp"

#include <QMenuBar>

#include <memory>

#include "TemplateWrapper/Singleton.hpp"

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent) noexcept
        : QMainWindow(parent) {
    QMainWindow::setWindowTitle("Media Server Speaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    auto tabs = new Scopes::ControlTab(this);
    QMainWindow::setCentralWidget(tabs);

    auto menuBar = QMainWindow::menuBar();

    auto settings = menuBar->addMenu(tr("Settings"));
    settings->addSeparator();

    auto editMode = settings->addAction("Edit mode");
    editMode->setCheckable(true);
    connect(editMode, &QAction::toggled, [tabs](bool toggled) {
        emit
        tabs->editModeChanged(toggled);
    });

    auto wid = new QWidget(this);
    wid->resize(400, 400);
}

void MainWindow::startServer() noexcept {
    auto& ser = Wor::TemplateWrapper::Singleton<Wor::Network::TcpServer>::get();
    ser.start();
}
