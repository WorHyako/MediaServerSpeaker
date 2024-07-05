#pragma once

#include "IAction.hpp"

#include <QAction>

namespace Mss::Gui::Actions {

    /**
     * @brief
     *
     * @author
     */
    class LoadAction
            : public QAction,
              protected IAction {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit LoadAction(QObject *parent = nullptr, QWidget *caller = nullptr);

        /**
         * @brief Dtor.
         */
        ~LoadAction() override = default;

    public slots:

        /**
         * @brief
         */
        void execute() const noexcept override;
    };
}
