#pragma once

class QWidget;

namespace Mss::Gui::Actions {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class IAction {
    protected:
        /**
         * @brief Ctor.
         *
         * @param caller
         */
        explicit IAction(QWidget *caller)
                : _caller(caller) {};

        /**
         * @brief Dtor.
         */
        virtual ~IAction() = default;

        /**
         * @brief
         */
        virtual void execute() const noexcept = 0;

        QWidget *_caller;
    };
}
