#pragma once

#include "MovableBaseControl.hpp"

class QPushButton;

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

    private:
        QPushButton *_button;

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

    };
}