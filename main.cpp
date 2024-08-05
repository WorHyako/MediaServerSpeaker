#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Style/WorStyle.hpp"

#include "TemplateWrapper/Singleton.hpp"
#include "Network/TcpServer.hpp"

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    boost::asio::io_service ioService;
    auto& ser = Wor::TemplateWrapper::Singleton<Wor::Network::TcpServer>::get();

    boost::asio::ip::tcp::endpoint localEndPoint;
    localEndPoint.port(33000);
    auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
    localEndPoint.address(address);

    ser.init(ioService);
    ser.bindTo(localEndPoint);

    auto window = new Dialogs::MainWindow();
    window->startServer();
    std::thread t1([&ioService]() { ioService.run(); });
    window->show();

    app.setStyleSheet(Style::getWorStyle().c_str());
    t1.detach();

    return QApplication::exec();
}
