#pragma once

#include <QMenu>

namespace Mss::Gui::Controls::Menus {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ControlContextMenu
            : public QMenu {
    Q_OBJECT

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

    private slots:

        /**
         * @brief
         */
        void configure();

        /**
         * @brief
         */
        void reset();
    };
}
