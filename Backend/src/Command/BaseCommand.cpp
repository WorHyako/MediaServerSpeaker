#include "BaseCommand.hpp"

#include "pugixml.hpp"

#include "spdlog/spdlog.h"

#include "Wor/Network/TcpServer.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <sstream>

using namespace Mss::Backend::Command;
using namespace pugi;

void BaseCommand::addItem(CommandItem item) noexcept {
	_items.emplace_back(std::move(item));

	std::stringstream ss;
	ss << "Command has been changed: "
			<< str().c_str();
	spdlog::info(ss.str());
}

void BaseCommand::addItems(std::vector<CommandItem> items) noexcept {
	std::ranges::for_each(items,
						  [this](const CommandItem &each) {
							  addItem(each);
						  });
}

void BaseCommand::removeItem(CommandItem item) noexcept {
	removeItem(item.key());
}

void BaseCommand::removeItem(std::string key) noexcept {
	auto idx = indexOf(key);
	removeItem(idx);
}

void BaseCommand::removeItem() noexcept {
	_items.pop_back();
}

void BaseCommand::removeItem(std::uint16_t idx) noexcept {
	if (idx > _items.size()) {
		return;
	}
	_items.erase(std::begin(_items) + idx);
}

void BaseCommand::clean() noexcept {
	_items.clear();
}

bool BaseCommand::execute(std::string sessionName) const noexcept {
	std::stringstream ss;
	ss << "Command executing"
			<< str().c_str();
	spdlog::info(ss.str());

	auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
	auto session = server.session(sessionName);
	if (!session) {
		return false;
	}
	session->send(str());
	return true;
}

void BaseCommand::changeItem(CommandItem item) noexcept {
	auto idx = indexOf(item.key());
	if (idx == -1) {
		return;
	}
	_items.at(idx) = item;
}

void BaseCommand::changeItem(std::uint16_t idx, CommandItem item) noexcept {
	if (idx < std::size(_items)) {
		_items.at(idx) = item;
	}
}

std::int16_t BaseCommand::indexOf(std::string key) const noexcept {
	bool found = false;
	auto foundItem = std::find_if(std::begin(_items),
								  std::end(_items),
								  [&key, &found](const CommandItem &each) {
									  found = each.key() == key;
									  return found;
								  });

	return static_cast<std::int16_t>(found
		? std::distance(std::begin(_items), foundItem)
		: -1);
}

#pragma region Accessors/Mutators

void BaseCommand::set(const std::string &commandStr) noexcept {
	xml_document doc;
	xml_parse_result res = doc.load_string(commandStr.c_str());
	if (res.status != xml_parse_status::status_ok) {
		return;
	}
	xml_node root = doc.first_child();
	_tag = root.name();

	std::uint16_t t = std::distance(std::begin(root.attributes()), std::end(root.attributes()));
	_items.clear();
	_items.reserve(t);
	std::for_each(root.attributes_begin(),
				  root.attributes_end(),
				  [&items = _items](const pugi::xml_attribute &each) {
					  items.emplace_back(each.name(), each.value());
				  });
}

std::string BaseCommand::tag() const noexcept {
	return _tag;
}

std::vector<CommandItem> BaseCommand::items() const noexcept {
	return _items;
}

void BaseCommand::tag(std::string tag) noexcept {
	_tag = tag;
}

std::string BaseCommand::str() const noexcept {
	xml_document doc;
	doc.append_child(tag().c_str());
	std::ranges::for_each(_items,
						  [&doc](const CommandItem &each) {
							  auto root = doc.first_child();
							  auto attr = root.append_attribute(each.key().c_str());
							  attr.set_value(each.value().c_str());
						  });
	std::stringstream ss;
	doc.print(ss);
	return ss.str();
}

#pragma endregion Accessors/Mutators
