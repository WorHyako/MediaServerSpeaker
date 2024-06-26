#pragma once

#include "Button.hpp"

namespace MSS::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementButton
            : public Button {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ManagementButton(QWidget *parent);

        /**
         * @brief Dtor.
         */
        ~ManagementButton() override = default;

        /**
         * @brief
         *
         * @param e
         */
        void mouseMoveEvent(QMouseEvent *e) override;

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;

        /**
         * @brief
         *
         * @param e
         */
        void mouseReleaseEvent(QMouseEvent *e) override;

    private:
        bool _isResizable;
    };
}
