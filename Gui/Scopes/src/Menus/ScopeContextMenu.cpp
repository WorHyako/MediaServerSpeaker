#include "Menus/ScopeContextMenu.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/QuickButton.hpp"
#include "Controls/QuickTitle.hpp"
#include "Controls/Table.hpp"
#include "Controls/ManagementTextableButton.hpp"

#include "Creators/ControlCreator.hpp"

#include "Interfaces/IScope.hpp"

using namespace Mss::Gui::Scopes::Menus;
using namespace Mss::Gui::Controls;

namespace {

	/**
	 * @brief
	 *
	 * @tparam  TControlType
	 *
	 * @param   scope
	 *
	 * @author  WorHyako
	 */
	template <class TControlType>
	void addToScope(Mss::Gui::Scopes::IScope *scope) {
		auto control = ControlCreator<TControlType>::create();
		scope->addControl(control.release());
	}
}

ScopeContextMenu::ScopeContextMenu(Scopes::ControlType controlType, QWidget *parent) noexcept
	: QMenu(parent) {
	auto addNewMenu = new QMenu("Add new...");

	auto scope = dynamic_cast<Scopes::IScope *>(QMenu::parent());
	if (!scope) {
		return;
	}

	/**
	 * TODO: change to template parameters pack
	 */
	QList<QAction *> addActionList;
	if (controlType & Scopes::ControlType::ManagementTextableButton) {
		auto addButton = new QAction("Management Textable Button");
		std::ignore = connect(addButton,
							  &QAction::triggered,
							  [scope]() {
								  ::addToScope<ManagementTextableButton>(scope);
							  });

		addActionList.emplace_back(addButton);
	}

	if (controlType & Scopes::ControlType::ManagementButton) {
		auto addMButton = new QAction("Management button");
		std::ignore = connect(addMButton,
							  &QAction::triggered,
							  [scope]() {
								  ::addToScope<ManagementButton>(scope);
							  });
		addActionList.emplace_back(addMButton);
	}

	if (controlType & Scopes::ControlType::QuickButton) {
		auto addMButton = new QAction("Quick button");
		std::ignore = connect(addMButton,
							  &QAction::triggered,
							  [scope]() {
								  ::addToScope<QuickButton>(scope);
							  });
		addActionList.emplace_back(addMButton);
	}

	if (controlType & Scopes::ControlType::QuickTitle) {
		auto addMButton = new QAction("Quick title");
		std::ignore = connect(addMButton,
							  &QAction::triggered,
							  [scope]() {
								  ::addToScope<QuickTitle>(scope);
							  });
		addActionList.emplace_back(addMButton);
	}

	if (controlType & Scopes::ControlType::Table) {
		auto addMButton = new QAction("Table");
		std::ignore = connect(addMButton,
							  &QAction::triggered,
							  [scope]() {
								  ::addToScope<Table>(scope);
							  });
		addActionList.emplace_back(addMButton);
	}

	addNewMenu->addActions(addActionList);
	QMenu::addMenu(addNewMenu);

	auto loadAction = new QAction("Load");
	std::ignore = connect(loadAction,
						  &QAction::triggered,
						  [scope]() {
							  scope->loadControls();
						  });

	auto saveAction = new QAction("Save");
	std::ignore = connect(saveAction,
						  &QAction::triggered,
						  [scope]() {
							  scope->saveControls();
						  });

	auto clearAction = new QAction("Clear");
	std::ignore = connect(clearAction,
						  &QAction::triggered,
						  [scope]() {
							  scope->removeAllControls();
						  });

	QMenu::addActions({loadAction, saveAction, clearAction});
}
