#include "SettingDialog.hpp"

#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

#include "Pages/NetworkSettingPage.hpp"
#include "Pages/MidiSettingsPage.hpp"
#include "Pages/SqlSettingsPage.hpp"

using namespace Mss::Gui::Dialogs;

SettingDialog::SettingDialog(QWidget *parent) noexcept
	: QDialog(parent) {
	QDialog::setMinimumSize(400, 400);

	auto vLayout = new QVBoxLayout;
	QDialog::setLayout(vLayout);
	QDialog::setWindowTitle("Settings");

	auto tabWidget = new QTabWidget;
	tabWidget->setTabPosition(QTabWidget::West);
	vLayout->addWidget(tabWidget);

	auto commonLayout = new QHBoxLayout;

	auto okButton = new QPushButton("Ok");
	commonLayout->addWidget(okButton);
	vLayout->addLayout(commonLayout);

	auto networkPage = new Pages::NetworkSettingPage;
	tabWidget->addTab(networkPage, "Network");

	auto midiPage = new Pages::MidiSettingsPage;
	tabWidget->addTab(midiPage, "Midi");

	auto sqlPage = new Pages::SqlSettingsPage;
	tabWidget->addTab(sqlPage, "Sql");
}
