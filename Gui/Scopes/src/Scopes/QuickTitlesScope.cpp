#include "QuickTitlesScope.hpp"

#include "Controls/QuickTitle.hpp"
#include "Config.hpp"

#include <QVBoxLayout>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

QuickTitlesScope::QuickTitlesScope(QWidget *parent) noexcept
	: IScope(parent) {
	_controlsType = ControlType::QuickTitle;
	auto layout = new QVBoxLayout;
	QWidget::setLayout(layout);

	layout->setAlignment(Qt::AlignmentFlag::AlignTop);
	layout->setSpacing(5);
}

void QuickTitlesScope::addControl(QWidget *control) noexcept {
	control->setFixedHeight(50);

	QWidget::layout()->addWidget(control);
}

void QuickTitlesScope::removeControl(QWidget *control) noexcept {
	QWidget::layout()->removeWidget(control);
	control->deleteLater();
}

void QuickTitlesScope::removeAllControls() noexcept {
	auto children = QWidget::children();
	std::ranges::for_each(children,
						  [this](QObject *each) {
							  auto control = dynamic_cast<IControl *>(each);
							  if (!control) {
								  return;
							  }
							  removeControl(control);
						  });
}

void QuickTitlesScope::loadControls() noexcept {
	const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
	if (!parentTab) {
		return;
	}
	/**
	 * TODO: first thread
	 */
	removeAllControls();

	/**
	 * TODO: second thread
	 */
	std::string tabName(parentTab->accessibleName().toUtf8().constData());
	Config<QuickTitlesScope> config(tabName);
	if (!config.loadConfig()) {
		return;
	}

	auto controls = config.loadFromConfig<QuickTitle>();

	/**
	 * TODO: finish
	 */
	std::ranges::for_each(controls,
						  [this](auto &each) {
							  addControl(each.release());
						  });
}

void QuickTitlesScope::saveControls() noexcept {
	const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
	if (!parentTab) {
		return;
	}
	std::string tabName(parentTab->accessibleName().toUtf8().constData());
	Config<QuickTitlesScope> config(tabName);
	config.addToConfig<QuickTitle>(this);
	std::ignore = config.saveConfig();
}

#pragma region Callbacks

void QuickTitlesScope::editModeChange(bool toggled) {

}

#pragma endregion Callbacks
