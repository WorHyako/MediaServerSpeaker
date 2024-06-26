#pragma once

#include "IAction.hpp"

#include <QAction>

namespace MSS::Gui::Actions {

    class AddControlAction
            : public QAction,
              protected IAction {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit AddControlAction(QObject *parent = nullptr, QWidget *caller = nullptr);

        /**
         * @brief Dtor.
         */
        ~AddControlAction() override = default;

    public slots:

        /**
         * @brief
         */
        void execute() const noexcept override;
    };
}
