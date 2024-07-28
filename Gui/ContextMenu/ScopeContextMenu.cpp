#include "ScopeContextMenu.hpp"

#include "Controls/ControlCreator.hpp"
#include "Controls/ManagementButton.hpp"
#include "Controls/QuickButton.hpp"
#include "Controls/QuickTitle.hpp"
#include "Controls/ManagementTextableButton.hpp"

using namespace Mss::Gui::ContextMenu;
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
    template<class TControlType>
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

    QList<QAction *> addActionList;
    if (controlType & Scopes::ControlType::ManagementTextableButton) {
        auto addButton = new QAction("Management Textable Button");
        connect(addButton, &QAction::triggered, [scope]() {
            ::addToScope<ManagementTextableButton>(scope);
        });

        addActionList.emplace_back(addButton);
    }

    if (controlType & Scopes::ControlType::ManagementButton) {
        auto addMButton = new QAction("Management button");
        connect(addMButton, &QAction::triggered, [scope]() {
            ::addToScope<ManagementButton>(scope);
        });
        addActionList.emplace_back(addMButton);
    }

    if (controlType & Scopes::ControlType::QuickButton) {
        auto addMButton = new QAction("Quick button");
        connect(addMButton, &QAction::triggered, [scope]() {
            ::addToScope<QuickButton>(scope);
        });
        addActionList.emplace_back(addMButton);
    }

    if (controlType & Scopes::ControlType::QuickTitle) {
        auto addMButton = new QAction("Quick title");
        connect(addMButton, &QAction::triggered, [scope]() {
            ::addToScope<QuickTitle>(scope);
        });
        addActionList.emplace_back(addMButton);
    }

    addNewMenu->addActions(addActionList);
    QMenu::addMenu(addNewMenu);

    auto loadAction = new QAction("Load");
    connect(loadAction, &QAction::triggered, [scope]() {
        scope->loadControls();
    });

    auto saveAction = new QAction("Save");
    connect(saveAction, &QAction::triggered, [scope]() {
        scope->saveControls();
    });

    auto clearAction = new QAction("Clear");
    connect(clearAction, &QAction::triggered, [scope]() {
        scope->removeAllControls();
    });

    QMenu::addActions({ loadAction, saveAction, clearAction });
}
