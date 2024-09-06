#include "Midi/ServerRoad.hpp"

#include "Wor/Wrappers/Singleton.hpp"
#include "Wor/Network/TcpServer.hpp"

using namespace Mss::Backend::Midi;

ServerRoad::ServerRoad(std::string sessionName) noexcept
	: _sessionName(std::move(sessionName)),
	  _isActive(false) {
}

void ServerRoad::go() noexcept {
	const auto &command = _isActive ? _activeCommand : _deactiveCommand;;
	std::printf("Execute command: %s\n", command->str().c_str());
	auto &server = Wor::Wrappers::Singleton<Wor::Network::TcpServer>::get();
	const auto &session = server.session(_sessionName);
	if (!session) {
		return;
	}
	session->send(command->str());

	_isActive = !_isActive;
}

#pragma region Accessors/Mutators

void ServerRoad::sessionName(std::string sessionName) noexcept {
	_sessionName = std::move(sessionName);
}

std::string ServerRoad::sessionName() const noexcept {
	return _sessionName;
}

void ServerRoad::activeCommand(WorCommandPtr command) noexcept {
	_activeCommand = std::move(command);
}

void ServerRoad::deactiveCommand(WorCommandPtr command) noexcept {
	_deactiveCommand = std::move(command);
}

ServerRoad::WorCommandPtr ServerRoad::currentCommand() const noexcept {
	return _isActive ? _activeCommand : _deactiveCommand;
}

#pragma endregion Accessors/Mutators
