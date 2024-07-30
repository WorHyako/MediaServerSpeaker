#include "MainWindow.hpp"

#include "Tabs/ControlTab.hpp"

#include <QMenuBar>

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
    connect(editMode, &QAction::toggled, [tabs](bool toggled){
        emit tabs->editModeChanged(toggled);
    });
}
