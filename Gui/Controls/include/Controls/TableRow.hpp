#pragma once

#include <QWidget>

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class TableRow
            : public QWidget {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit TableRow(QWidget *parent = nullptr);

        /**
         * @brief Ctor.
         *
         * @param key
         *
         * @param value
         *
         * @param parent
         */
        TableRow(const QString& key, const QString& value, QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~TableRow() override = default;

#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        QPair<QString, QString> getKeyValue() const noexcept;

        /**
         * @brief
         *
         * @param keyValue
         */
        void setKeyValue(const QPair<QString, QString>& keyValue) noexcept;

#pragma endregion Accessors/Mutators

    };
}
