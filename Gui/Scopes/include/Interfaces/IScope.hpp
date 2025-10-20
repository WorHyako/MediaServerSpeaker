#pragma once

#include <cstdint>

#include <QWidget>

namespace Mss::Gui::Scopes {
/**
 * @brief Contains list of controls, that uses for @code ContextMenu @endcode filling.
 *
 * @author WorHyako
 */
enum class ControlType : std::uint8_t {
    /**
     * No control
     */
    None = 0b0,

    /**
     * @see Gui::Controls::ManagementTextableButton.
     */
    ManagementTextableButton = 0b1,

    /**
     * @see Gui::Controls::ManagementButton.
     */
    ManagementButton = 0b10,

    /**
     * @see Gui::Controls::QuickButton.
     */
    QuickButton = 0b100,

    /**
     * @see Gui::Controls::QuickTitle.
     */
    QuickTitle = 0b1000,

    /**
     * @see Gui::Controls::Table.
     */
    Table = 0b10000
};

/**
 * @brief Operator
 *
 * @param lhs Left hand side object.
 *
 * @param rhs Right hand side object.
 *
 * @return
 *
 * @author WorHyako
 */
[[nodiscard]]
inline ControlType operator|(ControlType lhs, ControlType rhs) {
    return static_cast<ControlType>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

/**
 * @brief
 *
 * @param lhs Left hand side object.
 *
 * @param rhs Right hand side object.
 *
 * @return
 *
 * @author WorHyako
 */
[[nodiscard]]
inline bool operator&(ControlType lhs, ControlType rhs) {
    return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

/**
 * @brief Abstract class for all scopes. Dictates main methods for scope's behaviour.
 *
 * @author WorHyako
 */
class IScope : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit IScope(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~IScope() noexcept override = default;

    /**
     * @brief Adds control to scope.
     *
     * @param control New control.
     */
    virtual void add_control(QWidget *control) noexcept = 0;

    /**
     * @brief Removes control from scope.
     *
     * @param control Control.
     */
    virtual void remove_control(QWidget *control) noexcept = 0;

    /**
     * @brief Removes all controls from scope.
     */
    virtual void remove_all_controls() noexcept = 0;

    /**
     * @brief Loads control from config.
     */
    virtual void load_controls() noexcept = 0;

    /**
     * @brief Save controls to config.
     */
    virtual void save_controls() noexcept = 0;

protected:
    /**
     * @brief Working mode, when it's available to change control's properties and settings.
     *
     * Edit mode is controlling by MainWindow.
     */
    bool edit_mode_;

    /**
     * @brief	Available controls for current scope.
     */
    ControlType controls_type_;

    /**
     * TODO: i don't know, what this method do...
     *
     * @brief
     *
     * @param children
     */
    virtual void edit_mode_change(bool edit_mode, QObjectList children) noexcept;

    /**
     * @brief Opens menu with list of available list of controls.
     *
     * @param controls_type Available controls.
     */
    virtual void open_menu(QMouseEvent *e, ControlType controls_type) noexcept;

#pragma region Callbacks

    /**
     * @brief Mouse press event. Uses for context menu calling.
     *
     * @param e Mouse event info.
     */
    void mousePressEvent(QMouseEvent *e) noexcept override;

    /**
     * @brief Painting event. Uses for style sheet applying.
     *
     * @param e Paint event.
     */
    void paintEvent(QPaintEvent *e) noexcept override;

#pragma endregion Callbacks
};
}
