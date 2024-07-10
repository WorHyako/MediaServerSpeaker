#include "CommandItem.hpp"

using namespace Mss::Backend::Command;

CommandItem::CommandItem(std::string key, std::string value) noexcept
        : _item { std::move(key), std::move(value) } {
}

std::string CommandItem::key() const noexcept {
    return _item.first;
}

std::string CommandItem::value() const noexcept {
    return _item.second;
}

bool CommandItem::empty() const noexcept {
    return _item.second.empty();
}
