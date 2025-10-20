#pragma once

#include "Interfaces/IScope.hpp"

namespace Mss::Gui::Scopes {
/**
 * @brief Scope for @code QuickTitle @endcode controls.
 *
 * Has methods to load/save controls.
 *
 * @author WorHyako
 */
class QuickTitlesScope final : public IScope {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit QuickTitlesScope(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~QuickTitlesScope() override = default;

    /**
     * @brief Adds control to scope.
     *
     * @param control New control.
     */
    void add_control(QWidget *control) noexcept override;

    /**
     * @brief Removes control from scope.
     *
     * @param control Control.
     */
    void remove_control(QWidget *control) noexcept override;

    /**
     * @brief Removes all controls from scope.
     */
    void remove_all_controls() noexcept override;

    /**
     * @brief Loads controls data from config and generate it in scope.
     */
    void load_controls() noexcept override;

    /**
     * @brief Save controls data to config.
     */
    void save_controls() noexcept override;

#pragma region Callbacks

  public slots:
    /**
     * @brief Slot to handle tab signal that edit mode was changed.
     *
     * @param toggled New edit mode value.
     */
    void edit_mode_change(bool toggled);

#pragma endregion Callbacks
};
}
