#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include <iostream>

using namespace Mss::Gui;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();
    window->show();

    return QApplication::exec();
}
