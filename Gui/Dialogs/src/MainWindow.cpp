#include "MainWindow.hpp"

#include "Creators/ControlCreator.hpp"
#include "SettingDialog.hpp"
#include "Tabs/ControlTab.hpp"

#include <QMenuBar>

#include <memory>

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow{ parent } {
    QMainWindow::setWindowTitle("Media Server Speaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    auto tabs{ new Scopes::ControlTab(this) };
    QMainWindow::setCentralWidget(tabs);

    auto menuBar{ QMainWindow::menuBar() };

    auto settings_menu{ menuBar->addMenu(tr("Preference")) };

    auto settings{ settings_menu->addAction("Edit...") };
    std::ignore = connect(settings, &QAction::triggered, [this](bool) {
        auto setting_dialog{ Controls::ControlCreator<SettingDialog>::create(this) };
        setting_dialog->show();
        std::ignore = setting_dialog.release();
    });

    settings_menu->addSeparator();

    auto edit_mode{ settings_menu->addAction("Edit mode") };
    edit_mode->setCheckable(true);
    std::ignore = connect(edit_mode, &QAction::toggled, [tabs](bool toggled) {
        emit tabs->edit_mode_changed(toggled);
    });
}
