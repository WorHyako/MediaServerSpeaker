#pragma once

#include "Interfaces/IMovableControl.hpp"

class QLineEdit;

class QPushButton;

namespace Mss::Gui::Controls {
/**
 * @brief
 *
 * @author WorHyako
 */
class ManagementTextableButton final : public IMovableControl {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit ManagementTextableButton(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~ManagementTextableButton() override = default;

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
     * @param text
     */
    void set_text(std::string text) noexcept override;

    /**
     * @brief Control's text accessor for QLineEdit.
     *
     * @return Control's text.
     */
    [[nodiscard]]
    std::string get_text() const noexcept override;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

  public slots:
    void command_changed() noexcept override;

#pragma endregion Callbacks
};
}
