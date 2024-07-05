#pragma once

#include <QMenu>

#include <memory>

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ContextMenu :
            public QMenu {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ContextMenu(QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~ContextMenu() override = default;

        /**
         * @brief
         *
         * @param actions
         */
        void setActions(const std::vector<QAction *> &actions) noexcept;

    private:
        std::vector<std::unique_ptr<QAction>> _actions;
    };
}
