#pragma once

#include <QWidget>

namespace Mss::Gui::Controls {

/**
 * @brief Object represents row item for Table.
 *
 * Row repeat CommandItem view.
 *
 * @author WorHyako
 */
class TableRow final : public QWidget {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param key_value Key-value.
     *
     * @param parent Parent widget.
     */
    explicit TableRow(const QPair<QString, QString> &key_value = {}, QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~TableRow() override = default;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Key-value accessor.
     *
     * @return Key-value.
     */
    [[nodiscard]]
    QPair<QString, QString> key_value() const noexcept;

    /**
     * @brief Key-value mutator.
     *
     * @param key_value New key-value.
     */
    void key_value(const QPair<QString, QString> &key_value) noexcept;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

  signals:
    /**
     * @brief Signal to Table with data of modified kay-value
     *
     * @param keyValue Modified key-value.
     *
     * @param sender Self-pointer to identify modified row.
     */
    void keyValueChanged(QPair<QString, QString> keyValue, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks
};
}
