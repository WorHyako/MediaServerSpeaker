#pragma once

#include <QtCore>

class QWidget;

class QMouseEvent;

namespace MSS::Gui::Components {

    /**
     * @brief
     *
     * @author
     */
    class WidgetTransformComponent{
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit WidgetTransformComponent(QWidget *parent);

        /**
         * @brief Dtor.
         */
        virtual ~WidgetTransformComponent() = default;

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
