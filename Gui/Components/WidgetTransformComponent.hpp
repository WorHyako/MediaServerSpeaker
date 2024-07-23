#pragma once

#include <QObject>
#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {

    /**
     * @brief
     *
     * @author
     */
    class WidgetTransformComponent
            : public QObject {
    Q_OBJECT

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
        ~WidgetTransformComponent() override = default;

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
