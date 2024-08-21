#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Style/WorStyle.hpp"

#include "TemplateWrapper/Singleton.hpp"
#include "Network/TcpServer.hpp"
#include "Network/Utils/IoService.hpp"

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    boost::asio::ip::tcp::endpoint localEndPoint;
    localEndPoint.port(33000);
    auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
    localEndPoint.address(address);

    auto &ser = TemplateWrapper::Singleton<Network::TcpServer>::get();

    if (!ser.bindTo(localEndPoint)) {
        ser.stop();
        return 9;
    }
    if (ser.start(); !ser.isRunning()) {
        return 9;
    }

    auto window = new Dialogs::MainWindow();
    window->show();

    Network::Utils::IoService::run();
//    auto t1 = Wor::Network::Utils::IoService::isRunning();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    Wor::Network::Utils::IoService::stop();
//    auto t2 = Wor::Network::Utils::IoService::isRunning();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    Wor::Network::Utils::IoService::run();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    auto t3 = Wor::Network::Utils::IoService::isRunning();
    app.setStyleSheet(Style::getWorStyle().c_str());

    return QApplication::exec();
}
