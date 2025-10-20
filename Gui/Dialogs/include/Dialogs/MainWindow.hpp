#pragma once

#include <QMainWindow>

namespace Mss::Gui::Dialogs {

/**
 * @brief Main application window.
 *
 * @author WorHyako
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Destructor.
     */
    ~MainWindow() override = default;

#pragma region Callbacks
  signals:

    /**
     * @brief Signal emitted when edit mode is changed.
     *
     * @param value New edit mode value.
     */
    void edit_mode_changed(bool value);

#pragma endregion Callbacks
};
}
