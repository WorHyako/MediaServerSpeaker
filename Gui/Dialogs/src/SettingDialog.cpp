#include "SettingDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include "Network/TcpServer.hpp"
#include "TemplateWrapper/Singleton.hpp"

using namespace Mss::Gui::Dialogs;

SettingDialog::SettingDialog(QWidget *parent) noexcept
        : QDialog(parent) {
    auto vLayout = new QVBoxLayout(this);
    QDialog::setLayout(vLayout);

    QDialog::setWindowTitle("Settings");

    auto &server = Wor::TemplateWrapper::Singleton<Wor::Network::TcpServer>::get();

    {
        /**
         * End point Layout
         */
        auto hLayout = new QHBoxLayout;

        auto addressText = new QTextEdit("127.0.0.1");
        hLayout->addWidget(addressText);

        auto portText = new QTextEdit("33100");
        hLayout->addWidget(portText);

        _serverConnectButton = new QPushButton("Apply");
        std::string buttonStyle("QPushButton {background-color: \"#%s\"; }",
                                server.isRunning() ? "00ff00" : "ff0000");

        connect(_serverConnectButton, &QPushButton::pressed, [addressText, portText, &server]() {
            std::string address = addressText->toPlainText().toUtf8().constData();
            bool portConversation(false);
            auto port = portText->toPlainText().toInt(&portConversation);
            if (!portConversation) {
                std::printf("Wrong port symbols\n");
            }
            boost::asio::ip::tcp::endpoint endpoint;
            endpoint.port(port);
            endpoint.address(boost::asio::ip::make_address_v4(address));
            if (server.bindTo(endpoint)) {
                std::printf("Success in binding to local port\n");
            } else {
                std::printf("Fail in binding to local port\n");
            }
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
    connect(refreshButton, &QPushButton::pressed, [this]() {
        this->refreshServerStatus();
    });
    vLayout->addWidget(refreshButton);

    {
        /**
         * Common buttons layout
         */
        auto hLayout = new QHBoxLayout;

        auto okButton = new QPushButton("Ok");
        connect(okButton, &QPushButton::pressed, [this]() {
            this->close();
        });
        hLayout->addWidget(okButton);

        vLayout->addLayout(hLayout);
    }
}

void SettingDialog::refreshServerStatus() noexcept {
    auto &server = Wor::TemplateWrapper::Singleton<Wor::Network::TcpServer>::get();
    auto sessionList = server.sessionList();

    std::string buttonStyle("QPushButton {background-color: \"#%s\"; }",
                            server.isRunning() ? "00ff00" : "ff0000");

    while (_sessionListLayout->count() > 0) {
        auto c = _sessionListLayout->count();
        auto idx = _sessionListLayout->count() - 1;
        auto item = _sessionListLayout->itemAt(idx);
        _sessionListLayout->removeItem(item);
        auto itemChildren = item->layout()->children();
        while(item->layout()->count() > 0) {
            auto itemChild = item->layout()->itemAt(0);
            item->layout()->removeItem(itemChild);
            itemChild->widget()->deleteLater();
        }
        std::for_each(std::begin(itemChildren), std::end(itemChildren), [layout = item->layout()](QObject *each) {
            layout->removeWidget(dynamic_cast<QWidget *>(each));
            each->deleteLater();
        });
        item->layout()->deleteLater();
    }

    std::for_each(std::begin(sessionList), std::end(sessionList),
                  [&sessionLayout = _sessionListLayout](const Wor::Network::TcpSession::ptr &session) {
                      auto hLayout = new QHBoxLayout;

                      QString endpointStr(session->endpoint().address().to_string().c_str()
                                          + QString(":")
                                          + QString::number(session->endpoint().port()));

                      auto endPointText = new QLabel;
//                      auto endPointText = new QTextEdit;
                      endPointText->setText(endpointStr);

                      hLayout->addWidget(endPointText);

                      sessionLayout->addLayout(hLayout);
                  });
}
