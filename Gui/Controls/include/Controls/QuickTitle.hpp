#pragma once

#include "BaseControl.hpp"

class QTextEdit;

class QPushButton;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickTitle
            : public BaseControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickTitle(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~QuickTitle() override = default;

    private:
        QTextEdit *_textEdit;

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
