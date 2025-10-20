#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {
/**
 * @brief Movable control to management tasks.
 *
 * By default, has midi and server road.
 *
 * @author WorHyako
 */
class ManagementButton final : public IMovableControl {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit ManagementButton(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~ManagementButton() override = default;

  private:
    /**
     * @brief Control's QPushButton.
     */
    QPushButton *button_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Central control's text mutator.
     *
     * @param text New text.
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

#pragma region Callbacks

    /**
     * TODO: is it useless??
     *
     * @brief
     */
    void command_changed() noexcept override;

#pragma endregion Callbacks
};
}
