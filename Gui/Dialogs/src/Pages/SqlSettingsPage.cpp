#include "Pages/SqlSettingsPage.hpp"

#include <QLabel>
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

	auto hostLayout = new QHBoxLayout;
	auto hostlabel = new QLabel("Host:");
	hostLayout->addWidget(hostlabel);

	_hostText = new QTextEdit(dbParameters.host.c_str());
	hostLayout->addWidget(_hostText);

	auto portLabel = new QLabel("Port:");
	hostLayout->addWidget(portLabel);

	_portText = new QTextEdit(QString::number(dbParameters.port));
	hostLayout->addWidget(_portText);

	vLayout->addLayout(hostLayout);

	auto userLayout = new QHBoxLayout;
	auto userNameLabel = new QLabel("Username:");
	userLayout->addWidget(userNameLabel);

	_userNameText = new QTextEdit(dbParameters.user.c_str());
	userLayout->addWidget(_userNameText);

	auto userPasswordLabel = new QLabel("Password:");
	userLayout->addWidget(userPasswordLabel);

	_userPasswordText = new QTextEdit(dbParameters.password.c_str());
	userLayout->addWidget(_userPasswordText);

	auto dbNameLabel = new QLabel("Database name:");
	userLayout->addWidget(dbNameLabel);

	_dbNameText = new QTextEdit(dbParameters.dbName.c_str());
	userLayout->addWidget(_dbNameText);

	vLayout->addLayout(userLayout);
}

void SqlSettingsPage::refreshSqlStatus() noexcept {
	auto &sqlManager = Wor::Wrappers::Singleton<Wor::Sql::MySqlManager>::get();

	Wor::Sql::DataBaseParameters dbParams;
	dbParams.host = _hostText->toPlainText().toStdString();
	dbParams.port = _portText->toPlainText().toInt();
	dbParams.user = _userNameText->toPlainText().toStdString();
	dbParams.password = _userPasswordText->toPlainText().toStdString();
	dbParams.dbName = _dbNameText->toPlainText().toStdString();
	dbParams.dbType = "mysql";
	if (!sqlManager.dpParameters(dbParams)) {
		return;
	}
	std::ignore = sqlManager.tryToConnect();
}
