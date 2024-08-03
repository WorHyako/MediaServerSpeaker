#include "MainWindow.hpp"

#include <QApplication>

#include "Style/WorStyle.hpp"

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    auto window = new Dialogs::MainWindow();

    boost::asio::io_service ioContext;
    window->initServer(ioContext, static_cast<std::uint16_t>(33100));
    std::thread t1([&ioContext]() { ioContext.run(); });

    window->show();

    app.setStyleSheet(Style::getWorStyle().c_str());
    t1.detach();

    return QApplication::exec();
}
