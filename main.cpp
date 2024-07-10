#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include <iostream>

#include "Command/ActionCommand.hpp"

using namespace Mss::Gui;
using namespace Mss::Backend;

int main(int argc, char **argv) {
    auto command = new Command::ActionCommand;
    command->addItem({"key", "value"});
    command->addItem({"key2", "value2"});
    command->removeItem("key");
    std::cout << command->str();
//    return -1;

    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();
    window->show();

    return QApplication::exec();
}
