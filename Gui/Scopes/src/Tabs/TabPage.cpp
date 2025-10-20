#include "Tabs/TabPage.hpp"

#include "ManagementScope.hpp"
#include "QuickButtonScope.hpp"
#include "QuickTitlesScope.hpp"

#include <QGridLayout>

using namespace Mss::Gui::Scopes;

TabPage::TabPage(QWidget *parent) noexcept
	: QWidget{parent} {
	auto *layout { new QGridLayout(this)};
	QWidget::setLayout(layout);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 2);

	/**
	 * QuickTitles Scope
	 */
	auto quick_titles_scope { new Scopes::QuickTitlesScope(this)};
	std::ignore = connect(this, SIGNAL(edit_mode_changed(bool)), quick_titles_scope, SLOT(edit_mode_changed(bool)));
	layout->addWidget(quick_titles_scope, 0, 0, 6, 1);

	/**
	 * QuickButtons Scope
	 */
	auto quick_button_scope { new Scopes::QuickButtonScope(this)};
	std::ignore = connect(this, SIGNAL(edit_mode_changed(bool)), quick_button_scope, SLOT(edit_mode_changed(bool)));
	layout->addWidget(quick_button_scope, 6, 0, 4, 1);

	/**
	 * Management scope
	 */
	auto management_scope { new ManagementScope(this)};
	std::ignore = connect(this, SIGNAL(edit_mode_changed(bool)), management_scope, SLOT(edit_mode_changed(bool)));
	layout->addWidget(management_scope, 0, 1, 10, 2);
}

void TabPage::edit_mode_change(bool toggled) {
	emit edit_mode_changed(toggled);
}
