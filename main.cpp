#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Style/WorStyle.hpp"

using namespace Mss::Gui;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();
    window->show();

    app.setStyleSheet(Style::getWorStyle().c_str());

    return QApplication::exec();
}
