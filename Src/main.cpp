#include "Dialogs/MainWindow.hpp"

#include <QApplication>

using namespace MSS::Gui;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();

    return QApplication::exec();
    return 1;
}
