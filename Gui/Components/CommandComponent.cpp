#include "CommandComponent.hpp"

#include "Command/CommandBuilder.hpp"
#include "Command/BaseCommand.hpp"

using namespace Mss::Gui::Components;
using namespace Mss::Backend::Command;

CommandComponent::CommandComponent() noexcept {
    _command = CommandBuilder<BaseCommand>::build();
}

const ICommand *CommandComponent::getCommand() const noexcept {
    return _command.get();
}

void CommandComponent::setCommand(ICommand *command) noexcept {
    _command.reset(command);
}
