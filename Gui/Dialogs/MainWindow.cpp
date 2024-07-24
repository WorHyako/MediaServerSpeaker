#include "Dialogs/MainWindow.hpp"

#include "Scopes/ControlTab.hpp"

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent) noexcept
        : QMainWindow(parent) {
    QMainWindow::setWindowTitle("Media Server Speaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    auto tabs = new Scopes::ControlTab(this);
    QMainWindow::setCentralWidget(tabs);
}
