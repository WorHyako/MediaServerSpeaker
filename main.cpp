#include <QApplication>

#include "Wor/Wrappers/Singleton.hpp"
#include "Wor/Network/TcpServer.hpp"
#include "Wor/Network/Utils/IoService.hpp"
#include "Wor/Sql/MySqlManager.hpp"
#include "Wor/Log/Log.hpp"

#include "ConfData/AuthData.hpp"
#include "Dialogs/MainWindow.hpp"

#ifdef LOG_TO_FILE

#include <spdlog/sinks/basic_file_sink.h>

#endif

import mss.backend;
import mss.gui;
import worlib.midi;

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
	Log::configureLogger();

#ifdef LOG_TO_FILE

	auto localLogger = spdlog::basic_logger_mt("local_logger", "log/log.txt", true);
	spdlog::set_default_logger(localLogger);

#endif

	QApplication app(argc, argv);

	/**
	 * SQL
	 */
	auto &manager = Wrappers::Singleton<Sql::MySqlManager>::get();
	manager.configure(Mss::ConfData::authParameters);
	auto connectRes = manager.tryToConnect();

	// return 0;

	/**
	 * Tcp Server
	 */
	Network::TcpServer::Endpoint localEndPoint;
	localEndPoint.port(33000);
	boost::asio::ip::address address{boost::asio::ip::make_address_v4("127.0.0.1")};
	localEndPoint.address(address);

	auto &server = Wrappers::Singleton<Network::TcpServer>::get();

	if (!server.bindTo(localEndPoint)) {
		server.stop();
		return 9;
	}
	if (server.start(); !server.bound()) {
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
		if (!server.bound()) {
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

	app.setStyleSheet(Style::get_wor_style().c_str());

	return QApplication::exec();
}
