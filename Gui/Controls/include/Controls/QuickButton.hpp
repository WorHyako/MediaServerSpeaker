#pragma once

#include "BaseControl.hpp"

class QPushButton;

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

    protected:
        QPushButton *_button;

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @param text
         */
        void text(std::string text) noexcept override;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string text() const noexcept override;

#pragma endregion Accessors/Mutators

    };
}
