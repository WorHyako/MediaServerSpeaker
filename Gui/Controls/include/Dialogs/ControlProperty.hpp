#pragma once

#include "Command/BaseCommand.hpp"

#include <QDialog>

#include <memory>

class QVBoxLayout;

class QHBoxLayout;

namespace Mss::Gui::Controls {
class IControl;
}

namespace Mss::Gui::Controls::Dialogs {
/**
 * @brief Dialog to modify control's properties.
 *
 * Contains temporary fields to not modify original controls before applying by "Apply" button.
 *
 * @author WorHyako
 */
class ControlProperty final : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     *
     * @param parent Parent widget.
     */
    explicit ControlProperty(QWidget *parent = nullptr) noexcept;

    /**
     * @brief Dtor.
     */
    ~ControlProperty() override = default;

  private:
    /**
     * @brief Adds item to command layout with selected CommandItem data.
     *
     * @param item Command item to add.
     *
     * @param unique Should be item unique or not.
     *
     * Uses when command already filled, but need to fill command layout.
     */
    void add_command_item_hlayout(const Backend::Command::CommandItem &item = {}, bool unique = true) noexcept;

    /**
     * @brief Remove selected item from command layout.
     *
     * @param hlayout Item to delete.
     */
    void remove_command_item_hlayout(QHBoxLayout *hlayout) noexcept;

    /**
     * @brief Original control to modify.
     */
    Controls::IControl *control_;

    /**
     * @brief Layout with command items.
     */
    QVBoxLayout *command_layout_;

    /**
     * @brief Temporary control name field to save modified content.
     */
    std::string control_name_;

    /**
     * @brief Temporary control session name field to save modified content.
     */
    std::string session_name_;

    /**
     * @brief Temporary control midi button id field to save modified content.
     */
    std::uint8_t midi_button_id_;

    /**
     * @brief Temporary command to test it.
     */
    std::unique_ptr<Backend::Command::BaseCommand> test_command_;

  public:
#pragma region Callbacks

  signals:
    /**
     * @brief
     *
     * TODO: looks like it's useless method
     *
     * @param command_str
     */
    void full_command_changed(const QString &command_str);

  public slots:
    /**
     * @brief Refresh full command field and fill command text field.
     *
     * @param idx Index of a modified command item.
     *
     * @param item New command item.
     */
    void refresh_command(std::uint16_t idx, const Backend::Command::CommandItem &item);

    /**
     * @brief Apply all modified fields to selected controls.
     */
    void apply_changed() noexcept;

#pragma endregion Callbacks
};
}
