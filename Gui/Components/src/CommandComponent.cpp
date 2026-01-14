#include "CommandComponent.hpp"

#include "Command/BaseCommand.hpp"

import mss.backend;

using namespace Mss::Gui::Components;
using namespace Mss::Backend::Command;

CommandComponent::CommandComponent() noexcept
    : session_name_{ "session_x" } {
    command_ = CommandBuilder<BaseCommand>::build();
}

bool CommandComponent::execute() const noexcept {
    return command_->execute(session_name_);
}

#pragma region Accessors / Mutators

std::shared_ptr<ICommand> CommandComponent::command() const noexcept {
    return command_;
}

void CommandComponent::command(ICommand *command) noexcept {
    command_.reset(command);
}

void CommandComponent::set_session_name(std::string session_name) noexcept {
    session_name_ = std::move(session_name);
}

std::string CommandComponent::get_session_name() const noexcept {
    return session_name_;
}

#pragma endregion Accessors / Mutators
