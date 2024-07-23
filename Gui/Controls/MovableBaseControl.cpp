#include "MovableBaseControl.hpp"

using namespace Mss::Gui::Controls;

MovableBaseControl::MovableBaseControl(QWidget *parent) noexcept
        : WidgetTransformComponent(parent),
          BaseControl(parent) {
}
