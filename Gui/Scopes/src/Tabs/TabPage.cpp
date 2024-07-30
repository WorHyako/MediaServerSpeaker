#include "Tabs/TabPage.hpp"

#include "ManagementScope.hpp"
#include "QuickButtonScope.hpp"
#include "QuickTitlesScope.hpp"

#include <QGridLayout>

using namespace Mss::Gui::Scopes;

TabPage::TabPage(QWidget *parent) noexcept
        : QWidget(parent) {
    auto *layout = new QGridLayout(this);
    QWidget::setLayout(layout);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 2);

    /**
     * QuickButtons Scope
     */
    auto quickButtonScope = new Scopes::QuickButtonScope(this);
    layout->addWidget(quickButtonScope, 1, 0, 1, 1);
    quickButtonScope->show();

    /**
     * QuickTitles Scope
     */
    auto quickTitlesScope = new Scopes::QuickTitlesScope(this);
    layout->addWidget(quickTitlesScope, 0, 0, 1, 1);

    /**
     * Management scope
     */
    auto managementScope = new ManagementScope(this);
    layout->addWidget(managementScope, 0, 1, 2, 1);
}
