#include "MainWindow.hpp"

#include "Creators/ControlCreator.hpp"
#include "Tabs/ControlTab.hpp"
#include "SettingDialog.hpp"

#include <QMenuBar>

#include <memory>

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent) noexcept
        : QMainWindow(parent) {
    QMainWindow::setWindowTitle("Media Server Speaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    auto tabs = new Scopes::ControlTab(this);
    QMainWindow::setCentralWidget(tabs);

    auto menuBar = QMainWindow::menuBar();

    auto settingsMenu = menuBar->addMenu(tr("Preference"));

    auto settings = settingsMenu->addAction("Edit...");
    connect(settings, &QAction::triggered, [this](bool) {
        auto settingsDialog = Controls::ControlCreator<Dialogs::SettingDialog>::create(this);
        settingsDialog->show();
        std::ignore = settingsDialog.release();
    });

    settingsMenu->addSeparator();

    auto editMode = settingsMenu->addAction("Edit mode");
    editMode->setCheckable(true);
    connect(editMode, &QAction::toggled, [tabs](bool toggled) {
        emit
        tabs->editModeChanged(toggled);
    });

    auto wid = new QWidget(this);
    wid->resize(400, 400);
}
