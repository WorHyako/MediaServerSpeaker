#include "Pages/NetworkSettingPage.hpp"

#include "Wor/Network/TcpServer.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <QGraphicsWidget>

#include "Config/Config.hpp"

using namespace Mss::Gui::Dialogs::Pages;

NetworkSettingPage::NetworkSettingPage(QWidget *parent) noexcept
	: QWidget(parent),
	  _serverConnectButton(nullptr) {
	auto vLayout = new QVBoxLayout(this);
	QWidget::setLayout(vLayout);

	{
		/**
		 * End point Layout
		 */
		auto hLayout = new QHBoxLayout;

		auto addressLabel = new QLabel("Host:");
		hLayout->addWidget(addressLabel);

		auto addressText = new QLineEdit("127.0.0.1");
		addressText->setMaximumHeight(30);
		hLayout->addWidget(addressText);

		auto portLabel = new QLabel("Port:");
		hLayout->addWidget(portLabel);

		auto portText = new QLineEdit("33000");
		portText->setMaximumHeight(30);
		hLayout->addWidget(portText);

		auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
		_serverConnectButton = new QPushButton("Apply");
		std::string buttonStyle("QPushButton {background-color: \"#%s\"; }",
								server.isRunning() ? "00ff00" : "ff0000");

		std::ignore = connect(_serverConnectButton,
							  &QPushButton::pressed,
							  [addressText, portText]() {
								  auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
								  std::string address = addressText->text().toUtf8().constData();
								  bool portConversation(false);
								  auto port = portText->text().toInt(&portConversation);
								  if (!portConversation) {
									  return;
								  }
								  boost::asio::ip::tcp::endpoint endpoint;
								  endpoint.port(port);
								  endpoint.address(boost::asio::ip::make_address_v4(address));
								  std::ignore = server.bindTo(endpoint);
							  });
		hLayout->addWidget(_serverConnectButton);

		vLayout->addLayout(hLayout);
	}

	/**
	 * Session list Layout
	 */
	_sessionListLayout = new QVBoxLayout;
	vLayout->addLayout(_sessionListLayout);

	auto refreshButton = new QPushButton("Refresh sessions");
	std::ignore = connect(refreshButton,
						  &QPushButton::pressed,
						  [this]() {
							  this->refreshServerStatus();
						  });
	vLayout->addWidget(refreshButton);
}

void NetworkSettingPage::refreshServerStatus() noexcept {
	auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
	auto sessionList = server.sessionList();

	std::string buttonStyle("QPushButton {background-color: \"#%s\"; }",
							server.isRunning() ? "00ff00" : "ff0000");

	while (_sessionListLayout->count() > 0) {
		auto idx = _sessionListLayout->count() - 1;
		auto item = _sessionListLayout->itemAt(idx);
		_sessionListLayout->removeItem(item);
		auto itemChildren = item->layout()->children();
		while (item->layout()->count() > 0) {
			auto itemChild = item->layout()->itemAt(0);
			item->layout()->removeItem(itemChild);
			itemChild->widget()->deleteLater();
		}
		std::ranges::for_each(itemChildren,
							  [layout = item->layout()](QObject *each) {
								  layout->removeWidget(dynamic_cast<QWidget *>(each));
								  each->deleteLater();
							  });
		item->layout()->deleteLater();
	}

	std::ranges::for_each(sessionList,
						  [&sessionLayout = _sessionListLayout](Wor::Network::TcpSession::ptr &session) {
							  auto hLayout = new QHBoxLayout;

							  QString endpointStr(session->endpoint().address().to_string().c_str()
									  + QString(":")
									  + QString::number(session->endpoint().port()));

							  auto endPointText = new QLabel;
							  endPointText->setText(endpointStr);
							  hLayout->addWidget(endPointText);

							  auto sessionName = new QLineEdit(session->name().c_str());
							  std::ignore = connect(sessionName,
													&QLineEdit::textChanged,
													[sessionName, session]() {
														session->name(sessionName->text().toUtf8().constData());
													});
							  hLayout->addWidget(sessionName);

							  sessionLayout->addLayout(hLayout);
						  });
}
