#include "BaseCommand.hpp"

#include "pugixml.hpp"

#include <sstream>

using namespace Mss::Backend::Command;

void BaseCommand::addItem(CommandItem item) noexcept {
    _items.emplace_back(std::move(item));

    std::printf("Command has been changed: %s\n", str().c_str());
}

void BaseCommand::addItems(std::vector<CommandItem> items) noexcept {
    std::for_each(std::begin(items), std::end(items), [this](const CommandItem &each) {
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

std::string BaseCommand::str() const noexcept {
    pugi::xml_document doc;
    doc.append_child(getTag().c_str());
    std::for_each(std::begin(_items), std::end(_items), [&doc](const CommandItem &each) {
        auto root = doc.first_child();
        auto attr = root.append_attribute(each.key().c_str());
        attr.set_value(each.value().c_str());
    });
    std::stringstream ss;
    doc.print(ss);
    return ss.str();
}

void BaseCommand::clean() noexcept {
    _items.clear();
}

bool BaseCommand::execute(std::string socketName) const noexcept {
    std::printf("Execute command: %s\n", str().c_str());
    return true;
}

std::string BaseCommand::getTag() const noexcept {
    return _tag;
}

std::vector<CommandItem> BaseCommand::getItems() const noexcept {
    return _items;
}

void BaseCommand::markTag(std::string tag) noexcept {
    _tag = tag;
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
    auto foundItem = std::find_if(std::begin(_items), std::end(_items), [&key, &found](const CommandItem &each) {
        if (each.key() == key) {
            found = true;
            return true;
        }
        return false;
    });

    return static_cast<std::int16_t>(found
                                     ? std::distance(std::begin(_items), foundItem)
                                     : -1);
}

void BaseCommand::set(const std::string &commandStr) noexcept {
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_string(commandStr.c_str());
    if (res.status != pugi::xml_parse_status::status_ok) {
        return;
    }
    pugi::xml_node root = doc.first_child();
    _tag = root.name();

    std::uint16_t t = std::distance(root.attributes().begin(), root.attributes().end());
    _items.clear();
    _items.reserve(t);
    std::for_each(root.attributes_begin(), root.attributes_end(), [&items = _items](const pugi::xml_attribute& each){
        items.emplace_back(each.name(), each.value());
    });
}
