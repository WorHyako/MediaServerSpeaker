#pragma once

#include "IAction.hpp"

#include <QAction>

namespace Mss::Gui::Actions {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class RenameAction
            : public QAction,
              protected IAction {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit RenameAction(QObject *parent = nullptr, QWidget *caller = nullptr);

        /**
         * @brief Dtor.
         */
        ~RenameAction() override = default;

    public slots:

        /**
         * @brief
         */
        void execute() const noexcept override;
    };
}
