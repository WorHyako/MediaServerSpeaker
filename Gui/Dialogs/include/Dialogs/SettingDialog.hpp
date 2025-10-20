#pragma once

#include <QDialog>

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Dialogs {

/**
 * @brief Settings dialog window.
 *
 * @author WorHyako
 */
class SettingDialog : public QDialog {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit SettingDialog(QWidget *parent = nullptr) noexcept;
};
}
