#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Config/ControlsConfig.hpp"

using namespace Mss::Gui;
//using namespace Mss::Backend;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();
    window->show();

    return QApplication::exec();
}
