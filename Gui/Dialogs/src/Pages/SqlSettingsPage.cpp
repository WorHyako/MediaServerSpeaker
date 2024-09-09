#include "Pages/SqlSettingsPage.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

#include "Wor/Sql/MySqlManager.hpp"
#include "Wor/Wrappers/Singleton.hpp"

using namespace Mss::Gui::Dialogs::Pages;

SqlSettingsPage::SqlSettingsPage(QWidget *parent) noexcept
	: QWidget(parent),
	  _userNameText(nullptr),
	  _userPasswordText(nullptr),
	  _hostText(nullptr),
	  _portText(nullptr),
	  _dbNameText(nullptr) {
	auto vLayout = new QVBoxLayout;
	QWidget::setLayout(vLayout);

	auto &sqlManager = Wor::Wrappers::Singleton<Wor::Sql::MySqlManager>::get();
	auto dbParameters = sqlManager.dpParameters();

	auto hLayout = new QHBoxLayout;
	auto labelLayout = new QVBoxLayout;
	auto textLayout = new QVBoxLayout;

	auto hostlabel = new QLabel("Host:");
	labelLayout->addWidget(hostlabel);

	_hostText = new QLineEdit(dbParameters.host.c_str());
	textLayout->addWidget(_hostText);

	auto portLabel = new QLabel("Port:");
	labelLayout->addWidget(portLabel);

	_portText = new QLineEdit(QString::number(dbParameters.port));
	textLayout->addWidget(_portText);

	auto userNameLabel = new QLabel("Username:");
	labelLayout->addWidget(userNameLabel);

	_userNameText = new QLineEdit(dbParameters.user.c_str());
	textLayout->addWidget(_userNameText);

	auto userPasswordLabel = new QLabel("Password:");
	labelLayout->addWidget(userPasswordLabel);

	_userPasswordText = new QLineEdit(dbParameters.password.c_str());
	textLayout->addWidget(_userPasswordText);

	auto dbNameLabel = new QLabel("Database name:");
	labelLayout->addWidget(dbNameLabel);

	_dbNameText = new QLineEdit(dbParameters.dbName.c_str());
	textLayout->addWidget(_dbNameText);

	hLayout->addLayout(labelLayout);
	hLayout->addLayout(textLayout);

	vLayout->addLayout(hLayout);
}

void SqlSettingsPage::refreshSqlStatus() noexcept {
	auto &sqlManager = Wor::Wrappers::Singleton<Wor::Sql::MySqlManager>::get();

	Wor::Sql::DataBaseParameters dbParams;
	dbParams.host = _hostText->text().toStdString();
	dbParams.port = _portText->text().toInt();
	dbParams.user = _userNameText->text().toStdString();
	dbParams.password = _userPasswordText->text().toStdString();
	dbParams.dbName = _dbNameText->text().toStdString();
	dbParams.dbType = "mysql";
	if (!sqlManager.dpParameters(dbParams)) {
		return;
	}
	std::ignore = sqlManager.tryToConnect();
}
