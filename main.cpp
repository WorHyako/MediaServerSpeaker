#include "Dialogs/MainWindow.hpp"

#include <QApplication>

#include "Command/BaseCommand.hpp"
#include "Midi/MidiRoadMap.hpp"
#include "Style/WorStyle.hpp"

#include "TemplateWrapper/Singleton.hpp"
#include "Midi/MidiKeyboard.hpp"
#include "Network/TcpServer.hpp"
#include "Network/Utils/IoService.hpp"

using namespace Mss::Gui;
using namespace Wor;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	/**
	 * Tcp Server
	 */
	boost::asio::ip::tcp::endpoint localEndPoint;
	localEndPoint.port(33000);
	auto address = boost::asio::ip::address(boost::asio::ip::make_address_v4("127.0.0.1"));
	localEndPoint.address(address);

	auto &server = TemplateWrapper::Singleton<Network::TcpServer>::get();

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
	auto &midi = TemplateWrapper::Singleton<Midi::MidiKeyboard>::get();
	midi.open();
	midi.inCallback([](const Midi::CallbackInfo::BaseCallbackInfo &callbackInfo) {
		auto &server = TemplateWrapper::Singleton<Network::TcpServer>::get();
		if (!server.isRunning()) {
			return;
		}
		server.sendToAll("Hello");
	});

	auto &commandRetransmitter = TemplateWrapper::Singleton<Mss::Backend::Midi::MidiRoadMap>::get();
	midi.inCallback([&commandRetransmitter](Midi::CallbackInfo::BaseCallbackInfo callbackInfo) {
		commandRetransmitter.transmit(callbackInfo);
	});

	auto window = new Dialogs::MainWindow();
	window->show();

	app.setStyleSheet(Style::getWorStyle().c_str());

	return QApplication::exec();
}
