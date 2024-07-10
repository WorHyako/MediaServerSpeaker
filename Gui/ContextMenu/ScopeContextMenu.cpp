#include "ScopeContextMenu.hpp"

using namespace Mss::Gui::ContextMenu;

ScopeContextMenu::ScopeContextMenu(Scopes::ControlType controlType, QWidget *parent) noexcept
        : QMenu(parent) {
    auto addNewMenu = new QMenu("Add new...");

    auto scope = dynamic_cast<Scopes::IScope *>(QMenu::parent());
    if (!scope) {
        return;
    }

    QList<QAction *> addActionList;
    if (controlType & Scopes::ControlType::Button) {
        auto addButton = new QAction("Button");
        connect(addButton, &QAction::triggered, [scope]() {
            scope->addControl(Scopes::ControlType::Button);
        });
        addActionList.emplace_back(addButton);
    }

    if (controlType & Scopes::ControlType::ManagementButton) {
        auto addMButton = new QAction("Management button");
        connect(addMButton, &QAction::triggered, [scope]() {
            scope->addControl(Scopes::ControlType::ManagementButton);
        });
        addActionList.emplace_back(addMButton);
    }

    if (controlType & Scopes::ControlType::QuickButton) {
        auto addMButton = new QAction("Quick button");
        connect(addMButton, &QAction::triggered, [scope]() {
            scope->addControl(Scopes::ControlType::QuickButton);
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

    QMenu::addActions({ loadAction, saveAction });
}
