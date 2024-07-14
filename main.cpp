#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include <iostream>

#include "Command/ActionCommand.hpp"
#include "Command/CommandBuilder.hpp"

using namespace Mss::Gui;
using namespace Mss::Backend;

int main(int argc, char **argv) {
    auto command = Command::CommandBuilder<Command::ActionCommand>::build(
            {{ "key1", "value1" },
             { "key2", "value2" }});
    command->addItem({ "key3", "value3" });
    command->removeItem("key2");
    std::cout << "Command: " << command->str() << '\n';
    command->changeItem({ "key3", "newValue3" });
    command->changeItem(20, { "20", "val20" });
    command->changeItem(0, { "newKey1", "newVal1" });

    std::cout << "Changed command: " << command->str() << '\n';
    command->removeItem(1);
    std::cout << "Removed item: " << command->str() << '\n';
//    return 2;

    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();
    window->show();

    return QApplication::exec();
}
