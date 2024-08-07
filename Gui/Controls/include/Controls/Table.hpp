#pragma once

#include "MovableBaseControl.hpp"

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Controls {
    class TableRow;
}

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
         *
         * @param keyValue
         */
        void keyValueChange(const QPair<QString, QString>& keyValue, TableRow *sender);

        /**
         * @brief
         */
        void addRow(const QPair<QString, QString> &pair = {}) noexcept;

        /**
         * @brief
         */
        void removeRow() noexcept;

        /**
         * @brief
         */
        void commandChanged() noexcept override;

        /**
         * @brief
         */
        void clear() noexcept;

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
