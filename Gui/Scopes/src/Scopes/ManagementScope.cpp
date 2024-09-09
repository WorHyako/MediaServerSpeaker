#include "Scopes/ManagementScope.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/ManagementTextableButton.hpp"
#include "Config/Config.hpp"

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

ManagementScope::ManagementScope(QWidget *parent) noexcept
        : IScope(parent) {
    IScope::_controlsType = ControlType::ManagementButton
                            | ControlType::ManagementTextableButton
                            | ControlType::Table;
}

void ManagementScope::addControl(QWidget *control) noexcept {
    auto worControl = dynamic_cast<IMovableControl *>(control);
    if (!worControl) {
        return;
    }

    worControl->editMode(_editMode);
    worControl->setParent(this);
    worControl->show();
}

void ManagementScope::removeControl(QWidget *control) noexcept {
	control->setParent(nullptr);
	control->deleteLater();
}

void ManagementScope::removeAllControls() noexcept {
    auto children = QWidget::children();
    std::for_each(std::begin(children), std::end(children), [this](QObject *each) {
        auto control = dynamic_cast<IMovableControl *>(each);
        if (!control) {
            return;
        }
        removeControl(control);
    });
}

void ManagementScope::loadControls() noexcept {
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

	Config<ManagementScope> config(tabName);
	if (!config.loadConfig()) {
		return;
	}

	auto mbControls = config.loadFromConfig<ManagementButton>();
	auto mtbControls = config.loadFromConfig<ManagementTextableButton>();

	WorQWidgetPtrVec controls;

	controls.reserve(std::size(mbControls) + std::size(mtbControls));
	controls.insert(std::cend(controls),
					std::make_move_iterator(std::begin(mbControls)),
					std::make_move_iterator(std::end(mbControls)));
	controls.insert(std::cend(controls),
					std::make_move_iterator(std::begin(mtbControls)),
					std::make_move_iterator(std::end(mtbControls)));

	/**
	 * TODO: finish
	 */
	std::ranges::for_each(controls,
						  [this](auto &each) {
							  addControl(each.release());
						  });
}

void ManagementScope::saveControls() noexcept {
	const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
	if (!parentTab) {
		return;
	}
	std::string tabName(parentTab->accessibleName().toUtf8().constData());
	Config<ManagementScope> config(tabName);
	config.addToConfig<ManagementButton>(this);
	config.addToConfig<ManagementTextableButton>(this);
	std::ignore = config.saveConfig();
}

#pragma region Callbacks

void ManagementScope::editModeChange(bool toggled) {
    auto children = QWidget::children();

    IScope::editModeChange(toggled, children);
}

void ManagementScope::mousePressEvent(QMouseEvent *e) noexcept {

    IScope::mousePressEvent(e);
}

#pragma endregion Callbacks
