#include "Menus/ScopeContextMenu.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/ManagementTextableButton.hpp"
#include "Controls/QuickButton.hpp"
#include "Controls/QuickTitle.hpp"
#include "Controls/Table.hpp"
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
    auto control{ ControlCreator<TControlType>::create() };
    scope->add_control(control.release());
}
}

ScopeContextMenu::ScopeContextMenu(Scopes::ControlType control_type, QWidget *parent) noexcept
    : QMenu{ parent } {
    auto add_new_menu{ new QMenu("Add new...") };

    auto scope { dynamic_cast<Scopes::IScope *>(QMenu::parent())};
    if (!scope) {
        return;
    }

    /**
     * TODO: change to template parameters pack
     */
    QList<QAction *> add_action_list;
    if (control_type & Scopes::ControlType::ManagementTextableButton) {
        auto add_button{ new QAction("Management Textable Button") };
        std::ignore = connect(add_button, &QAction::triggered, [scope]() {
            ::addToScope<ManagementTextableButton>(scope);
        });

        add_action_list.emplace_back(add_button);
    }

    if (control_type & Scopes::ControlType::ManagementButton) {
        auto add_m_button{ new QAction("Management button") };
        std::ignore = connect(add_m_button, &QAction::triggered, [scope]() {
            ::addToScope<ManagementButton>(scope);
        });
        add_action_list.emplace_back(add_m_button);
    }

    if (control_type & Scopes::ControlType::QuickButton) {
        auto add_m_button{ new QAction("Quick button") };
        std::ignore = connect(add_m_button, &QAction::triggered, [scope]() {
            ::addToScope<QuickButton>(scope);
        });
        add_action_list.emplace_back(add_m_button);
    }

    if (control_type & Scopes::ControlType::QuickTitle) {
        auto add_m_button{ new QAction("Quick title") };
        std::ignore = connect(add_m_button, &QAction::triggered, [scope]() {
            ::addToScope<QuickTitle>(scope);
        });
        add_action_list.emplace_back(add_m_button);
    }

    if (control_type & Scopes::ControlType::Table) {
        auto add_m_button{ new QAction("Table") };
        std::ignore = connect(add_m_button, &QAction::triggered, [scope]() {
            ::addToScope<Table>(scope);
        });
        add_action_list.emplace_back(add_m_button);
    }

    add_new_menu->addActions(add_action_list);
    QMenu::addMenu(add_new_menu);

    auto load_action{ new QAction("Load") };
    std::ignore = connect(load_action, &QAction::triggered, [scope]() {
        scope->load_controls();
    });

    const auto save_action{ new QAction("Save") };
    std::ignore = connect(save_action, &QAction::triggered, [scope]() {
        scope->save_controls();
    });

    const auto clear_action{ new QAction("Clear") };
    std::ignore = connect(clear_action, &QAction::triggered, [scope]() {
        scope->remove_all_controls();
    });

    QMenu::addActions({ load_action, save_action, clear_action });
}
