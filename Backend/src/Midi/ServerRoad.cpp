#include "Midi/ServerRoad.hpp"

#include "Wor/Network/TcpServer.hpp"
#include "Wor/Wrappers/Singleton.hpp"

#include <spdlog/spdlog.h>

using namespace Mss::Backend::Midi;

ServerRoad::ServerRoad(std::string session_name) noexcept
    : session_name_{ std::move(session_name) },
      is_active_{ false } {
}

void ServerRoad::go() noexcept {
    const auto &command{ is_active_ ? active_command_ : deactive_command_ };
    std::stringstream ss;
    ss << "ServerRoad. Command executing: " << command->str();
    spdlog::info(ss.str());
    auto &server{ Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get() };
    const auto &session{ server.session(session_name_) };
    if (!session) {
        return;
    }
    session->send(command->str());

    is_active_ = !is_active_;
}

#pragma region Accessors / Mutators

void ServerRoad::set_session_name(std::string session_name) noexcept {
    session_name_ = std::move(session_name);
}

std::string ServerRoad::get_session_name() const noexcept {
    return session_name_;
}

void ServerRoad::active_command(WorCommandPtr command) noexcept {
    active_command_ = std::move(command);
}

void ServerRoad::deactive_command(WorCommandPtr command) noexcept {
    deactive_command_ = std::move(command);
}

ServerRoad::WorCommandPtr ServerRoad::current_command() const noexcept {
    return is_active_ ? active_command_ : deactive_command_;
}

#pragma endregion Accessors / Mutators
