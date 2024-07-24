#include "BaseControl.hpp"

#include "ControlCreator.hpp"

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

BaseControl::BaseControl(QWidget *parent) noexcept
        : QWidget(parent),
          _menu(Controls::ControlCreator<ContextMenu::ControlContextMenu>::create(this)) {
}
