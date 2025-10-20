#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Controls {
class TableRow;
}

namespace Mss::Gui::Controls {
/**
 * @brief Movable control for managing tasks.
 *
 * By default, has midi and server road.
 *
 * @author WorHyako
 */
class Table final : public IMovableControl {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit Table(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~Table() override = default;

    /**
     * @brief Adds row to the end.
     *
     * @param pair Key-value pair for the new row.
     */
    void add_row(const QPair<QString, QString> &pair = {}) noexcept;

    /**
     * @brief Removes the last row.
     */
    void remove_row() noexcept;

    /**
     * @brief Clears all rows.
     */
    void clear() noexcept;

  private:
    /**
     * @brief Control's push button.
     */
    QPushButton *button_;

    /**
     * @brief Layout containing table rows.
     */
    QVBoxLayout *rows_layout_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the control's text for the push button.
     *
     * @param text New text.
     */
    void set_text(std::string text) noexcept override;

    /**
     * @brief Returns the control's text from the push button.
     *
     * @return Control's text.
     */
    [[nodiscard]]
    std::string get_text() const noexcept override;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

    /**
     * @brief Handles command changes.
     */
    void command_changed() noexcept override;

  public slots:
    /**
     * @brief Slot to handle signals from TableRow.
     *
     * @param key_value Modified key-value pair.
     * @param sender Modified row pointer.
     */
    void key_value_change(const QPair<QString, QString> &key_value, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks
};
}
