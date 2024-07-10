#pragma once

class QWidget;

namespace Mss::Gui::Actions {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class IAction {
    public:
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

    protected:
        QWidget *_caller;
    };
}
