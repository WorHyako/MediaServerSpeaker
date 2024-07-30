#pragma once

#include "MovableBaseControl.hpp"

class QTextEdit;
class QPushButton;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementTextableButton
            : public MovableBaseControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ManagementTextableButton(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~ManagementTextableButton() override = default;

    private:
        QTextEdit *_textEdit;

        QPushButton *_button;

    public slots:

        void commandChanged() noexcept override;

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
