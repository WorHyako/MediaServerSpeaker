#include "SettingDialog.hpp"

#include "Pages/MidiSettingsPage.hpp"
#include "Pages/NetworkSettingPage.hpp"
#include "Pages/SqlSettingsPage.hpp"

#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

using namespace Mss::Gui::Dialogs;

SettingDialog::SettingDialog(QWidget *parent) noexcept
    : QDialog{ parent } {
    QDialog::setMinimumSize(400, 400);

    auto v_layout{ new QVBoxLayout };
    QDialog::setLayout(v_layout);
    QDialog::setWindowTitle("Settings");

    auto tab_widget{ new QTabWidget };
    tab_widget->setTabPosition(QTabWidget::West);
    v_layout->addWidget(tab_widget);

    auto common_layout{ new QHBoxLayout };

    auto ok_button{ new QPushButton("Ok") };
    common_layout->addWidget(ok_button);
    v_layout->addLayout(common_layout);

    const auto network_page{ new Pages::NetworkSettingPage };
    tab_widget->addTab(network_page, "Network");

    const auto midi_page{ new Pages::MidiSettingsPage };
    tab_widget->addTab(midi_page, "Midi");

    const auto sql_page{ new Pages::SqlSettingsPage };
    tab_widget->addTab(sql_page, "Sql");
}
