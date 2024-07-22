#pragma once

#include <QPushButton>

#include "BaseControl.hpp"
#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButton
            : public QPushButton,
              public Components::WidgetTransformComponent,
              public BaseControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickButton(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~QuickButton() override = default;

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
         * @param text
         */
        void setText(std::string text) noexcept override;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string getText() const noexcept override;
    };
}
