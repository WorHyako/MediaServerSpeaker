#pragma once

#include <QPushButton>

#include "IControl.hpp"
#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class Button
            : public QPushButton,
              public Components::WidgetTransformComponent,
              public IControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit Button(QWidget *parent = nullptr) noexcept;

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
         * @param text
         */
        void setText(std::string text) noexcept override;

        /**
         * @brief
         *
         * @return
         */
        std::string getText() const noexcept override;

        /**
         * @brief
         *
         * @param command
         */
        void setCommand(std::string command) noexcept override;

        /**
         * @brief
         *
         * @return
         */
        std::string getCommand() const noexcept override;
    };
}