#pragma once

#include <QMenu>

namespace Mss::Gui::ContextMenu {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ControlContextMenu
            : public QMenu {
    public:
        /**
         * @brief Ctor.
         *
         * @param controlType
         *
         * @param parent
         */
        explicit ControlContextMenu(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~ControlContextMenu() override = default;
    };
}
