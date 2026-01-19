#include "Pages/NetworkSettingPage.hpp"

#include "Wor/Network/TcpServer.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <QGraphicsWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

import mss.gui.scopes;

using namespace Mss::Gui::Dialogs::Pages;

NetworkSettingPage::NetworkSettingPage(QWidget *parent) noexcept
    : QWidget{ parent },
      server_connect_button_{ nullptr } {
    auto v_layout{ new QVBoxLayout(this) };
    QWidget::setLayout(v_layout);

    {
        /**
         * End point Layout
         */
        auto h_layout{ new QHBoxLayout };

        const auto address_label{ new QLabel("Host:") };
        h_layout->addWidget(address_label);

        auto addressText{ new QLineEdit("127.0.0.1") };
        addressText->setMaximumHeight(30);
        h_layout->addWidget(addressText);

        const auto port_label{ new QLabel("Port:") };
        h_layout->addWidget(port_label);

        auto port_text { new QLineEdit("33000")};
        port_text->setMaximumHeight(30);
        h_layout->addWidget(port_text);

        const auto &server { Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get()};
        server_connect_button_ = new QPushButton("Apply");
        std::string buttonStyle("QPushButton {background-color: \"#%s\"; }", server.bound() ? "00ff00" : "ff0000");

        std::ignore = connect(server_connect_button_, &QPushButton::pressed, [addressText, port_text]() {
            auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
            const std::string_view address { addressText->text().toUtf8().constData()};
            bool portConversation(false);
            const auto port { port_text->text().toInt(&portConversation)};
            if (!portConversation) {
                return;
            }
            boost::asio::ip::tcp::endpoint endpoint;
            endpoint.port(port);
            endpoint.address(boost::asio::ip::make_address_v4(address));
            std::ignore = server.bindTo(endpoint);
        });
        h_layout->addWidget(server_connect_button_);

        v_layout->addLayout(h_layout);
    }

    /**
     * Session list Layout
     */
    session_list_layout_ = new QVBoxLayout;
    v_layout->addLayout(session_list_layout_);

    const auto refreshButton{ new QPushButton("Refresh sessions") };
    std::ignore = connect(refreshButton, &QPushButton::pressed, [this]() {
        this->refresh_server_status();
    });
    v_layout->addWidget(refreshButton);
}

void NetworkSettingPage::refresh_server_status() noexcept {
    auto &server{ Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get() };

    // std::string buttonStyle("QPushButton {background-color: \"#%s\"; }", server.bound() ? "00ff00" : "ff0000");

    while (session_list_layout_->count() > 0) {
        const auto idx{ session_list_layout_->count() - 1 };
        auto item{ session_list_layout_->itemAt(idx) };
        session_list_layout_->removeItem(item);
        auto itemChildren{ item->layout()->children() };
        while (item->layout()->count() > 0) {
            auto itemChild{ item->layout()->itemAt(0) };
            item->layout()->removeItem(itemChild);
            itemChild->widget()->deleteLater();
        }
        std::ranges::for_each(itemChildren, [layout = item->layout()](QObject *each) {
            layout->removeWidget(dynamic_cast<QWidget *>(each));
            each->deleteLater();
        });
        item->layout()->deleteLater();
    }

    auto session_list{ server.sessionList() };
    std::ranges::for_each(
        session_list,
        [&session_layout{ session_list_layout_ }](Wor::Network::TcpSession::ptr &session) {
            auto h_layout{ new QHBoxLayout };

            QString endpointStr(
                session->endpoint().address().to_string().c_str() + QString(":") +
                QString::number(session->endpoint().port())
            );

            auto end_point_text{ new QLabel };
            end_point_text->setText(endpointStr);
            h_layout->addWidget(end_point_text);

            auto session_name{ new QLineEdit(session->alias().c_str()) };
            std::ignore = connect(session_name, &QLineEdit::textChanged, [session_name, session]() {
                session->alias(session_name->text().toUtf8().constData());
            });
            h_layout->addWidget(session_name);

            session_layout->addLayout(h_layout);
        }
    );
}
