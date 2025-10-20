#include "Pages/SqlSettingsPage.hpp"

#include "Wor/Sql/MySqlManager.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

using namespace Mss::Gui::Dialogs::Pages;

SqlSettingsPage::SqlSettingsPage(QWidget *parent) noexcept
    : QWidget{ parent },
      user_name_text_{ nullptr },
      user_password_text_{ nullptr },
      host_text_{ nullptr },
      port_text_{ nullptr },
      db_name_text_{ nullptr } {
    auto vLayout{ new QVBoxLayout };
    QWidget::setLayout(vLayout);

    auto &sql_manager{ Wor::Wrappers::Singleton<Wor::Sql::MySqlManager>::get() };
    auto db_parameters{ sql_manager.dpParameters() };

    auto h_layout{ new QHBoxLayout };
    auto label_layout{ new QVBoxLayout };
    auto text_layout{ new QVBoxLayout };

    const auto host_label{ new QLabel("Host:") };
    label_layout->addWidget(host_label);

    host_text_ = new QLineEdit(db_parameters.host.c_str());
    text_layout->addWidget(host_text_);

    const auto port_label{ new QLabel("Port:") };
    label_layout->addWidget(port_label);

    port_text_ = new QLineEdit(QString::number(db_parameters.port));
    text_layout->addWidget(port_text_);

    const auto user_name_label{ new QLabel("Username:") };
    label_layout->addWidget(user_name_label);

    user_name_text_ = new QLineEdit(db_parameters.user.c_str());
    text_layout->addWidget(user_name_text_);

    const auto user_password_label{ new QLabel("Password:") };
    label_layout->addWidget(user_password_label);

    user_password_text_ = new QLineEdit(db_parameters.password.c_str());
    text_layout->addWidget(user_password_text_);

    const auto db_name_label{ new QLabel("Database name:") };
    label_layout->addWidget(db_name_label);

    db_name_text_ = new QLineEdit(db_parameters.dbName.c_str());
    text_layout->addWidget(db_name_text_);

    h_layout->addLayout(label_layout);
    h_layout->addLayout(text_layout);

    vLayout->addLayout(h_layout);
}

void SqlSettingsPage::refresh_sql_status() noexcept {
    auto &sql_manager{ Wor::Wrappers::Singleton<Wor::Sql::MySqlManager>::get() };

    Wor::Sql::DataBaseParameters db_params;
    db_params.host = host_text_->text().toStdString();
    db_params.port = port_text_->text().toInt();
    db_params.user = user_name_text_->text().toStdString();
    db_params.password = user_password_text_->text().toStdString();
    db_params.dbName = db_name_text_->text().toStdString();
    db_params.dbType = "mysql";
    if (!sql_manager.dpParameters(db_params)) {
        return;
    }
    std::ignore = sql_manager.tryToConnect();
}
