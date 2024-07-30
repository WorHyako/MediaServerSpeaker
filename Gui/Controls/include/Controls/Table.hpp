#pragma once

#include "MovableBaseControl.hpp"

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class Table
            : public MovableBaseControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit Table(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~Table() override = default;

    public slots:

        /**
         * @brief
         */
        void addRow() noexcept;

        /**
         * @brief
         */
        void removeRow() noexcept;

    private:
        QPushButton *_button;

        QVBoxLayout *_rowsLayout;

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
