#include "ControlTab.hpp"

#include "ManagementScope.hpp"

using namespace Mss::Gui::Scopes;

ControlTab::ControlTab(QWidget *parent)
        : QTabWidget(parent) {
    QTabWidget::setTabPosition(QTabWidget::South);

    auto scope = new ManagementScope;
    QTabWidget::addTab(scope, "1");

    auto scope2 = new ManagementScope;
    QTabWidget::addTab(scope2, "2");

    auto scope3 = new ManagementScope;
    QTabWidget::addTab(scope3, "3");
}
