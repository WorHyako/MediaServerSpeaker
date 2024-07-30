#pragma once

#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {

    /**
     * @brief
     *
     * @author WorHyako
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

    private:
        QWidget *_parent;

        QPoint _lastMousePressPosition;

        bool _canTransform;

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @param canTransform
         */
        void setCanTransform(bool canTransform) noexcept;

#pragma endregion Accessors/Mutators
    };
}
