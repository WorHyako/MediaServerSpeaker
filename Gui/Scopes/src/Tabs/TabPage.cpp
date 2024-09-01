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
	 * QuickTitles Scope
	 */
	auto quickTitlesScope = new Scopes::QuickTitlesScope(this);
	std::ignore = connect(this, SIGNAL(editModeChanged(bool)), quickTitlesScope, SLOT(editModeChange(bool)));
	layout->addWidget(quickTitlesScope, 0, 0, 6, 1);

	/**
	 * QuickButtons Scope
	 */
	auto quickButtonScope = new Scopes::QuickButtonScope(this);
	std::ignore = connect(this, SIGNAL(editModeChanged(bool)), quickButtonScope, SLOT(editModeChange(bool)));
	layout->addWidget(quickButtonScope, 6, 0, 4, 1);

	/**
	 * Management scope
	 */
	auto managementScope = new ManagementScope(this);
	std::ignore = connect(this, SIGNAL(editModeChanged(bool)), managementScope, SLOT(editModeChange(bool)));
	layout->addWidget(managementScope, 0, 1, 10, 2);
}

void TabPage::editModeChange(bool toggled) {
	emit editModeChanged(toggled);
}
