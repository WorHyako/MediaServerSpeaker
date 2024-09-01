#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Midi/MidiRoadMap.hpp"
#include "Style/WorStyle.hpp"

#include "Wor/Wrappers/Singleton.hpp"
#include "Wor/Midi/MidiKeyboard.hpp"
#include "Wor/Network/TcpServer.hpp"
#include "Wor/Network/Utils/IoService.hpp"
#include "Wor/Sql/MySqlManager.hpp"

#include "ConfData/AuthData.hpp"

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	/**
	 * SQL
	 */

	auto &manager = Wrappers::Singleton<Sql::MySqlManager>::get();
	manager.configure(Mss::ConfData::authParameters);
	auto connectRes = manager.tryToConnect();

	return 0;

	/**
	 * Tcp Server
	 */
	boost::asio::ip::tcp::endpoint localEndPoint;
	localEndPoint.port(33000);
	auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
	localEndPoint.address(address);

	auto &server = Wrappers::Singleton<Network::TcpServer>::get();

	if (!server.bindTo(localEndPoint)) {
		server.stop();
		return 9;
	}
	if (server.start(); !server.isRunning()) {
		return 9;
	}
	Network::Utils::IoService::run();

	/**
	 * Midi
	 */
	auto &midi = Wrappers::Singleton<Midi::MidiKeyboard>::get();
	midi.open();
	midi.inCallback([](const Midi::CallbackInfo::BaseCallbackInfo &callbackInfo) {
		auto &server = Wrappers::Singleton<Network::TcpServer>::get();
		if (!server.isRunning()) {
			return;
		}
		server.sendToAll("Hello");
	});

	auto &commandRetransmitter = Wrappers::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
	midi.inCallback([&commandRetransmitter](Midi::CallbackInfo::BaseCallbackInfo callbackInfo) {
		commandRetransmitter.transmit(callbackInfo);
	});

	auto window = new Dialogs::MainWindow();
	window->show();

	app.setStyleSheet(Style::getWorStyle().c_str());

	return QApplication::exec();
}
