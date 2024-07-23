#pragma once

#include "MovableBaseControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

#include <QPushButton>

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementButton
            : public MovableBaseControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ManagementButton(QWidget *parent = nullptr) noexcept;

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

    public:
#pragma region Accessors/Mutators

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

#pragma endregion Accessors/Mutators

    private:
        QPushButton *_button;
    };
}
