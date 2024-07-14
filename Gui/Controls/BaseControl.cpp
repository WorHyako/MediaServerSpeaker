#include "BaseControl.hpp"

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

const ICommand* BaseControl::getCommand() const noexcept {
    return _command.get();
}

void BaseControl::setCommand(ICommand* command) noexcept{
    _command.reset(command);
}
