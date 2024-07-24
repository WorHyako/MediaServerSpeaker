#pragma once

#include "BaseControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class MovableBaseControl
            : public BaseControl,
              public Components::WidgetTransformComponent {
    public:
        /**
         * @brief Ctor.
         */
        explicit MovableBaseControl(QWidget *parent) noexcept;

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
        void mouseReleaseEvent(QMouseEvent *e) override;

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;
    };
}
