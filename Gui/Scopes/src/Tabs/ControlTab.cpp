#include "Tabs/ControlTab.hpp"

#include "Tabs/TabPage.hpp"

using namespace Mss::Gui::Scopes;

ControlTab::ControlTab(QWidget *parent) noexcept
        : QTabWidget(parent) {
    QTabWidget::setTabPosition(QTabWidget::South);

    auto page1 = new TabPage;
    page1->setAccessibleName("tab1");
    connect(this, SIGNAL(editModeChanged(bool)), page1, SLOT(editModeChange(bool)));
    QTabWidget::addTab(page1, "tab1");

    auto page2 = new TabPage;
    connect(this, SIGNAL(editModeChanged(bool)), page2, SLOT(editModeChange(bool)));
    page2->setAccessibleName("tab2");
    QTabWidget::addTab(page2, "tab2");

}
