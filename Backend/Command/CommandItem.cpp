#include "CommandItem.hpp"

using namespace Mss::Backend::Command;

CommandItem::CommandItem(std::string key, std::string value) noexcept
        : _key(std::move(key)),
          _value(std::move(value)) {
}

std::string CommandItem::key() const noexcept {
    return _key;
}

std::string CommandItem::value() const noexcept {
    return _value;
}

bool CommandItem::empty() const noexcept {
    return _value.empty();
}
