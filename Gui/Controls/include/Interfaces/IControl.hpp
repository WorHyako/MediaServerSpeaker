#pragma once

#include "Components/CommandComponent.hpp"
#include "Components/MidiComponent.hpp"

#include <QWidget>

namespace Mss::Gui::Controls {

/**
 * @brief Abstract object for all wor controls. Names all control with "WorControl" name.
 *
 * Adds CommandComponent and MidiComponent.
 *
 * @author WorHyako
 */
class IControl : public QWidget, public Components::CommandComponent, public Components::MidiComponent {
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     */
    explicit IControl(QWidget *parent) noexcept;

    /**
     * @brief Destructor.
     */
    ~IControl() override = default;

    /**
     * @brief Creates server road.
     *
     * Takes data from MidiComponent, CommandComponent and registrar new road in MidiRoadMap if it's possible
     *
     */
    void create_server_road() const noexcept;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Edit mode mutator.
     *
     * Orient to calling only from wor scope objects.
     *
     * @param enable New edit mode value.
     */
    virtual void edit_mode(bool enable) noexcept;

    /**
     * @brief Control's text mutator.
     *
     * @param text New control's text.
     */
    virtual void set_text(std::string text) noexcept = 0;

    /**
     * @brief Control's text accessor.
     *
     * @return Control's text.
     */
    [[nodiscard]]
    virtual std::string get_text() const noexcept = 0;

#pragma endregion Accessors / Mutators

#pragma region Callbacks

    /**
     * @brief Mouse press event.
     *
     * Left mouse uses for road going.
     *
     * Right mouse uses for context menu calling.
     *
     * @param e Mouse event info.
     */
    void mousePressEvent(QMouseEvent *e) override;

  public slots:
    /**
     * @brief Slot to handle event of command changing.
     *
     * All children should to process event themselves to modify text fields.
     */
    virtual void command_changed() noexcept = 0;

    /**
     * @brief Painting event. Uses for style sheet applying.
     *
     * @param e Paint event.
     */
    void paintEvent(QPaintEvent *e) override;

#pragma endregion Callbacks
};
}
