#include "Dialogs/MainWindow.hpp"

#include "Scopes/QuickButtonScope.hpp"
#include "Scopes/ManagementScope.hpp"

#include <QGridLayout>

using namespace MSS::Gui::Dialogs;

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
     * Scope 1
     */
    auto scope = new Scopes::QuickButtonScope(root);
    _mainLayout->addWidget(scope, 0, 0, 1, 1);
    scope->show();

    _mainLayout->setColumnStretch(0, 1);
    _mainLayout->setColumnStretch(1, 2);

    /**
     * Empty widget
     */
//    _mainLayout->addWidget(new QWidget(root), 1, 0);

    /**
     * Scope 2
     */
    auto scope2 = new Scopes::ManagementScope(root);
    _mainLayout->addWidget(scope2, 0, 1, 2, 1);
    scope2->show();

    window()->show();
}
