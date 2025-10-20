#pragma once

#include "Interfaces/IControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {
/**
 * @brief Static control to management tasks. Uses only in @code QuickButtonScope @endcode.
 *
 * By default, has server road.
 *
 * @author WorHyako
 */
class QuickButton final : public IControl {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit QuickButton(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~QuickButton() override = default;

  private:
    /**
     * @brief Control's QPushButton.
     */
    QPushButton *button_;

  public:
#pragma region Accessors / Mutators
    /**
     * @brief Control's text mutator.
     *
     * @param text New control's text.
     */
    void set_text(std::string text) noexcept override;

    /**
     * @brief Control's text accessor.
     *
     * @return Control's text.
     */
    [[nodiscard]]
    std::string get_text() const noexcept override;

#pragma endregion Accessors / Mutators

  public:
#pragma region Callbacks

    /**
     * @brief
     */
    void command_changed() noexcept override;

#pragma endregion Callbacks
};
}
