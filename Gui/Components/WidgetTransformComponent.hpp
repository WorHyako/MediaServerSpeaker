#pragma once

#include <QtCore>

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

#pragma region Mutators

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

#pragma endregion Mutators

    public slots:

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
        void stopTransform(QMouseEvent *e) noexcept;

    protected:
        QWidget *_parent;

        bool _canResize;

        bool _canMove;

        QPoint _lastMousePressPosition;
    };
}
