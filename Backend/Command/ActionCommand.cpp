#include "ActionCommand.hpp"

#include <sstream>

namespace {
    constexpr std::string_view commandTag("action");
}

using namespace Mss::Backend::Command;

ActionCommand::ActionCommand() noexcept
        : _command() {
    ActionCommand::markCommandTag();
}

bool ActionCommand::execute(std::string socketName) const noexcept {
    return false;
}

void ActionCommand::markCommandTag() noexcept {
    auto root = _command.first_child();
    std::string tag(commandTag);
    if (root.empty()) {
        std::ignore = _command.append_child(tag.c_str());
    } else {
        std::ignore = root.set_name(tag.c_str());
    }
}

void ActionCommand::addItem(CommandItem item) noexcept {
    auto lastChild = _command.last_child();
    auto attr = lastChild.append_attribute(item.key().c_str());
    attr.set_name(item.key().c_str());
    attr.set_value(item.value().c_str());
    std::printf("Command created: %s\n", str().c_str());
}

void ActionCommand::removeItem(CommandItem item) noexcept {
    removeItem(item.key());
}

void ActionCommand::removeItem(std::string key) noexcept {
    auto root = _command.first_child();
    if (root.empty()) {
        return;
    }
    root.remove_attribute(key.c_str());
}

std::string ActionCommand::str() const noexcept {
    std::stringstream ss;
    _command.print(ss);
    return ss.str();
}

void ActionCommand::clean() noexcept {
    _command.reset();
    markCommandTag();
}
