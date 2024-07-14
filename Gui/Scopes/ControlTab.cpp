#include "ControlTab.hpp"

#include "TabPage.hpp"

using namespace Mss::Gui::Scopes;

ControlTab::ControlTab(QWidget *parent) noexcept
        : QTabWidget(parent) {
    QTabWidget::setTabPosition(QTabWidget::South);

    auto page1 = new TabPage;
    page1->setAccessibleName("tab1");
    QTabWidget::addTab(page1, "tab1");

    auto page2 = new TabPage;
    page2->setAccessibleName("tab2");
    QTabWidget::addTab(page2, "tab2");
    auto page3 = new TabPage;

    page3->setAccessibleName("tab3");
    QTabWidget::addTab(page3, "tab3");
}
