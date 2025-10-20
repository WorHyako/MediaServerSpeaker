#pragma once

#include <QWidget>

namespace Mss::Gui::Scopes {
/**
 * @brief Tab page for working space. Contains QuickTitlesScope, QuickButtonScope, ManagementScope.
 *
 * @author WorHyako
 *
 * @see ControlTab.
 */
class TabPage final : public QWidget {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit TabPage(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~TabPage() override = default;

  public slots:
    /**
     * @brief Slot to handle tab signal, that edit mode was changed.
     *
     * @param toggled New edit mode value.
     */
    void edit_mode_change(bool toggled);

  signals:
    /**
     * @brief Signal to notify all scopes about edit mode changing.
     *
     * @param toggled New edit mode value.
     */
    void edit_mode_changed(bool toggled);
};
}
