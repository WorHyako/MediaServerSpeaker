#include "Dialogs/MainWindow.hpp"

#include "Scopes/QuickButtonScope.hpp"
#include "Scopes/ControlTab.hpp"
#include "Scopes/QuickTitlesScope.hpp"

#include <QGridLayout>

using namespace Mss::Gui::Dialogs;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          _mainLayout(nullptr) {
    QMainWindow::setWindowTitle("MediaServerSpeaker");
    QMainWindow::resize(500, 400);
    QMainWindow::setMinimumSize(500, 400);

    const auto root = new QWidget(this);
    QMainWindow::setCentralWidget(root);

    _mainLayout = new QGridLayout(root);

    /**
     * QuickButtons Scope
     */
    auto quickButtonScope = new Scopes::QuickButtonScope(root);
    _mainLayout->addWidget(quickButtonScope, 1, 0, 1, 1);
    quickButtonScope->show();

    _mainLayout->setColumnStretch(0, 1);
    _mainLayout->setColumnStretch(1, 2);

    /**
     * Empty widget
     */
     auto quickTitlesScope = new Scopes::QuickTitlesScope(root);
    _mainLayout->addWidget(quickTitlesScope, 0, 0, 1, 1);

    /**
     * Management scope
     */
    auto tabControl = new Scopes::ControlTab(root);
    _mainLayout->addWidget(tabControl, 0, 1, 2, 1);
}
