#pragma once

#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {
/**
 * @brief Object to transform (move and resize) Qt Widgets.
 *
 * Designed for inheritance to add transformation functionality to other classes.
 *
 * Resizes widget with Alt modifier.
 *
 * Moves widget with Ctrl modifier.
 *
 * @usage
 * @code
 *     class Foo
 *         : public QWidget,
 *           public Components::WidgetTransformComponent {
 *     ...
 *
 *     void Foo::mouseMoveEvent(QMouseEvent *e) {
 *         Components::WidgetTransformComponent::doTransform(e);
 *         ...
 *     }
 *
 *     void Foo::mouseReleaseEvent(QMouseEvent *e) {
 *         Components::WidgetTransformComponent::stopTransform(e);
 *         ...
 *     }
 *
 *     void Foo::enableTransforming(bool enable) noexcept {
 *         Components::WidgetTransformComponent::canTransform(enable);
 *         ...
 *     }
 * @endcode
 *
 * @author WorHyako
 */
class WidgetTransformComponent {
  public:
    /**
     * @brief Constructor.
     *
     * @param parent Object to transform.
     */
    explicit WidgetTransformComponent(QWidget *parent) noexcept;

    /**
     * @brief Destructor.
     */
    virtual ~WidgetTransformComponent() noexcept = default;

    /**
     * @brief Performs transformation if modifier key is pressed (see class description).
     *
     * @param e Mouse event to get key modifiers and position.
     */
    void do_transform(QMouseEvent *e) noexcept;

    /**
     * @brief Resets the last mouse position.
     */
    void stop_transform() noexcept;

  private:
    QWidget *parent_;

    QPoint last_mouse_press_position_;

    bool can_transform_;

  public:
#pragma region Accessors / Mutators

    /**
     * @brief Sets the transforming flag.
     *
     * @param can_transform New value.
     */
    void can_transform(bool can_transform) noexcept;

#pragma endregion Accessors / Mutators
};
}
