#include "CommandComponent.hpp"

using namespace Mss::Gui::Components;
using namespace Mss::Backend::Command;

const ICommand *CommandComponent::getCommand() const noexcept {
    return _command.get();
}

void CommandComponent::setCommand(ICommand *command) noexcept {
    _command.reset(command);
}
