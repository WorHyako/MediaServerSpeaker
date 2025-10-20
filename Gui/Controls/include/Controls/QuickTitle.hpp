#pragma once

#include "Interfaces/IControl.hpp"

class QLineEdit;

class QPushButton;

namespace Mss::Gui::Controls {
/**
 * @brief Static control to management tasks. Uses only in @code QuickTittlesScope @endcode.
 *
 * By default, has server road.
 *
 * @author WorHyako
 */
class QuickTitle final : public IControl {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit QuickTitle(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~QuickTitle() override = default;

  private:
    /**
     * @brief Control's QLineEdit.
     */
    QLineEdit *text_edit_;

    /**
     * @brief Control's QPushButton.
     */
    QPushButton *button_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Control's text mutator for QLineEdit.
     *
     * @param text New text.
     */
    void set_text(std::string text) noexcept override;

    /**
     * @brief Control's text accessor for QLineEdit.
     *
     * @return Control's text from QLineEdit.
     */
    [[nodiscard]]
    std::string get_text() const noexcept override;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

    /**
     * @brief
     */
    void command_changed() noexcept override;

#pragma endregion Callbacks
};
}
