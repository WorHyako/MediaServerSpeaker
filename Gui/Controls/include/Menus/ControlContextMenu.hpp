#pragma once

#include <QMenu>

namespace Mss::Gui::Controls::Menus {

/**
 * @brief
 *
 * TODO: fill doc for this objects
 *
 * @author WorHyako
 */
class ControlContextMenu : public QMenu {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit ControlContextMenu(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~ControlContextMenu() override = default;

#pragma region Callbacks

  private slots:
    /**
     * @brief
     */
    void configure();

    /**
     * @brief
     */
    void reset();

#pragma endregion Callbakcs
};
}
