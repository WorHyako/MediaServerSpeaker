#include "BaseCommand.hpp"

#include "Wor/Network/TcpServer.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <sstream>

#include <pugixml.hpp>

#include <spdlog/spdlog.h>

using namespace Mss::Backend::Command;
using namespace pugi;

void BaseCommand::add_item(CommandItem item) noexcept {
    items_.emplace_back(std::move(item));

    std::stringstream ss;
    ss << "Command has been changed: " << str().c_str();
    spdlog::info(ss.str());
}

void BaseCommand::add_items(std::vector<CommandItem> items) noexcept {
    std::ranges::for_each(items,
                          [this](const CommandItem &each) {
                              add_item(each);
                          });
}

void BaseCommand::remove_item(CommandItem item) noexcept {
    remove_item(item.key());
}

void BaseCommand::remove_item(std::string key) noexcept {
    const auto idx{ indexOf(key) };
    remove_item(idx);
}

void BaseCommand::remove_item() noexcept {
    items_.pop_back();
}

void BaseCommand::remove_item(std::uint16_t idx) noexcept {
    if (idx > std::size(items_)) {
        return;
    }
    items_.erase(std::begin(items_) + idx);
}

void BaseCommand::clean() noexcept {
    items_.clear();
}

bool BaseCommand::execute(std::string session_name) const noexcept {
    std::stringstream ss;
    ss << "Command executing" << str().c_str();
    spdlog::info(ss.str());

    auto &server{ Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get() };
    const auto session{ server.session(std::move(session_name)) };
    if (!session) {
        return false;
    }
    session->send(str());
    return true;
}

void BaseCommand::change_item(CommandItem item) noexcept {
    const auto idx{ indexOf(item.key()) };
    if (idx == -1) {
        return;
    }
    items_.at(idx) = item;
}

void BaseCommand::change_item(std::uint16_t idx, CommandItem item) noexcept {
    if (idx < std::size(items_)) {
        items_.at(idx) = item;
    }
}

std::int16_t BaseCommand::indexOf(std::string key) const noexcept {
    bool found{ false };
    const auto found_item{ std::ranges::find_if(items_,
                                                [&key, &found](const CommandItem &each) {
                                                    found = each.key() == key;
                                                    return found;
                                                }) };

    return static_cast<std::int16_t>(found ? std::distance(std::begin(items_), found_item) : -1);
}

#pragma region Accessors / Mutators

void BaseCommand::set(const std::string &command_str) noexcept {
    xml_document doc;
    const xml_parse_result res{ doc.load_string(command_str.c_str()) };
    if (res.status != xml_parse_status::status_ok) {
        return;
    }
    xml_node root{ doc.first_child() };
    tag_ = root.name();

    auto t{ std::distance(std::begin(root.attributes()), std::end(root.attributes())) };
    items_.clear();
    items_.reserve(t);
    std::ranges::for_each(root.attributes(),
                          [&items{ items_ }](const pugi::xml_attribute &each) {
                              items.emplace_back(each.name(), each.value());
                          });
}

std::string BaseCommand::get_tag() const noexcept {
    return tag_;
}

std::vector<CommandItem> BaseCommand::items() const noexcept {
    return items_;
}

void BaseCommand::set_tag(std::string tag) noexcept {
    tag_ = tag;
}

std::string BaseCommand::str() const noexcept {
    xml_document doc;
    doc.append_child(get_tag().c_str());
    std::ranges::for_each(items_,
                          [&doc](const CommandItem &each) {
                              auto root{ doc.first_child() };
                              auto attr{ root.append_attribute(each.key().c_str()) };
                              attr.set_value(each.value().c_str());
                          });
    std::stringstream ss;
    doc.print(ss);
    return ss.str();
}

#pragma endregion Accessors / Mutators
