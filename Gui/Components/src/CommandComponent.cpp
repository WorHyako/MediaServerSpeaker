#include "CommandComponent.hpp"

#include "Command/CommandBuilder.hpp"
#include "Command/BaseCommand.hpp"

using namespace Mss::Gui::Components;
using namespace Mss::Backend::Command;

CommandComponent::CommandComponent() noexcept
        : _sessionName("session_x") {
    _command = CommandBuilder<BaseCommand>::build();
}

bool CommandComponent::execute() const noexcept {
    return _command->execute(_sessionName);
}

#pragma region Accessors/Mutators

ICommand *CommandComponent::command() const noexcept {
    return _command.get();
}

void CommandComponent::command(ICommand *command) noexcept {
    _command.reset(command);
}

void CommandComponent::sessionName(std::string sessionName) noexcept {
    _sessionName = std::move(sessionName);
}

std::string CommandComponent::sessionName() const noexcept {
    return _sessionName;
}

#pragma endregion Accessors/Mutators
