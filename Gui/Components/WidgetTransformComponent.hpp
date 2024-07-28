#pragma once

#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {

    /**
     * @brief
     *
     * @author
     */
    class WidgetTransformComponent {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit WidgetTransformComponent(QWidget *parent) noexcept;

        /**
         * @brief Dtor.
         */
        virtual ~WidgetTransformComponent() = default;

    public:

        /**
         * @brief
         *
         * @param e
         */
        void doTransform(QMouseEvent *e) noexcept;

        /**
         * @brief
         *
         * @param e
         */
        void stopTransform(QMouseEvent *) noexcept;

    protected:
        QWidget *_parent;

        QPoint _lastMousePressPosition;

        bool _canResize;

        bool _canMove;

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @param canMove
         */
        void setCanMove(bool canMove) noexcept;

        /**
         * @brief
         *
         * @param canMove
         */
        void setCanResize(bool canResize) noexcept;

#pragma endregion Accessors/Mutators
    };
}
