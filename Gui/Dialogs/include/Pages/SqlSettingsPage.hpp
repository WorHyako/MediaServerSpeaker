#pragma once

#include <QWidget>

class QLineEdit;

namespace Mss::Gui::Dialogs::Pages {
/**
 * @brief SQL settings page widget.
 *
 * @author WorHyako
 */
class SqlSettingsPage : public QWidget {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit SqlSettingsPage(QWidget *parent = nullptr) noexcept;

  private:
    /**
     * @brief Refreshes the SQL connection status.
     */
    void refresh_sql_status() noexcept;

    QLineEdit *user_name_text_;

    QLineEdit *user_password_text_;

    QLineEdit *host_text_;

    QLineEdit *port_text_;

    QLineEdit *db_name_text_;
};
}
