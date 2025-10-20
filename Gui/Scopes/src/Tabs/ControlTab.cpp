#include "Tabs/ControlTab.hpp"

#include "Tabs/TabPage.hpp"

using namespace Mss::Gui::Scopes;

ControlTab::ControlTab(QWidget *parent) noexcept
    : QTabWidget{ parent } {
    QTabWidget::setTabPosition(QTabWidget::South);

    auto page1{ new TabPage };
    page1->setAccessibleName("tab1");
    std::ignore = connect(this, SIGNAL(edit_mode_changed(bool)), page1, SLOT(edit_mode_change(bool)));
    QTabWidget::addTab(page1, "tab1");

    auto page2{ new TabPage };
    std::ignore = connect(this, SIGNAL(edit_mode_changed(bool)), page2, SLOT(edit_mode_change(bool)));
    page2->setAccessibleName("tab2");
    QTabWidget::addTab(page2, "tab2");
}
