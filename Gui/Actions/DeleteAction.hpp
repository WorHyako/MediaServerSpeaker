#pragma once

#include "IAction.hpp"

#include <QAction>

namespace MSS::Gui::Actions {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class DeleteAction
            : public QAction,
              protected IAction {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit DeleteAction(QObject *parent = nullptr, QWidget *caller = nullptr);

        /**
         * @brief Dtor.
         */
        ~DeleteAction() override = default;

    public slots:

        /**
         * @brief
         */
        void execute() const noexcept override;
    };
}
