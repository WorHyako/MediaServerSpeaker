#pragma once

#include "Scopes/IScope.hpp"

#include <QMenu>

namespace Mss::Gui::ContextMenu {

    /**
     * @brief
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
    class ScopeContextMenu
            : public QMenu {
    public:
        /**
         * @brief Ctor.
         *
         * @param controlType
         *
         * @param parent
         */
        explicit ScopeContextMenu(Scopes::ControlType controlType,
                                  QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~ScopeContextMenu() override = default;
    };
}
