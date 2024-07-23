#pragma once

#include <QPushButton>

#include "BaseControl.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButton
            : public BaseControl {
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

    protected:
        QPushButton *_button;
    };
}
