#pragma once

#include "Interfaces/IScope.hpp"

#include <QMenu>

namespace Mss::Gui::Scopes::Menus {

/**
 * @brief	Context menu for Wor scopes.
 *
 * @usage
 * @code
 *          auto menu = new ScopeContextMenu(ControlType::ManagementButton |
 *                                           ControlType::Button,
 *                                           parent);
 * @endcode
 *
 * @author  WorHyako
 */
class ScopeContextMenu final : public QMenu {
  public:
    /**
     * @brief	Ctor.
     *
     * @param	control_type	Available control type.
     *
     * @param	parent		Parent widget.
     */
    explicit ScopeContextMenu(ControlType control_type, QWidget *parent = nullptr) noexcept;

    /**
     * @brief	Dtor.
     */
    ~ScopeContextMenu() override = default;
};
}
