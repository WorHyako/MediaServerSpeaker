#pragma once

#include <QPushButton>

#include "Components/WidgetTransformComponent.hpp"

namespace MSS::Gui::Controls {

    class ContextMenu;

    /**
     * @brief
     *
     * @author WorHyako
     */
    class Button
            : public QPushButton,
              protected Components::WidgetTransformComponent {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit Button(QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~Button() override = default;

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

        /**
         * @brief
         *
         * @param contextMenuEnable
         */
        void setContextMenuEnable(bool contextMenuEnable) noexcept;

    protected:
        bool _isContextMenuEnable;

        ContextMenu *_contextMenu;
    };
}