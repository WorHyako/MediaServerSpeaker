#include "CommandItem.hpp"

using namespace Mss::Backend::Command;

CommandItem::CommandItem(std::string key, std::string value) noexcept
	: key_{std::move(key)},
	  value_{std::move(value)} {
}

#pragma region Accessors / Mutators

std::string CommandItem::key() const noexcept {
	return key_;
}

std::string CommandItem::value() const noexcept {
	return value_;
}

bool CommandItem::empty() const noexcept {
	return value_.empty();
}

#pragma endregion Accessors / Mutators
