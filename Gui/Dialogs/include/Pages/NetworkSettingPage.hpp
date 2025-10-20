#pragma once

#include <QWidget>

class QPushButton;
class QVBoxLayout;

namespace Mss::Gui::Dialogs::Pages {

/**
 * @brief Network settings page widget.
 *
 * @author WorHyako
 */
class NetworkSettingPage : public QWidget {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit NetworkSettingPage(QWidget *parent = nullptr) noexcept;

  private:
    /**
     * @brief Refreshes the server connection status.
     */
    void refresh_server_status() noexcept;

    QVBoxLayout *session_list_layout_;

    QPushButton *server_connect_button_;
};
}
