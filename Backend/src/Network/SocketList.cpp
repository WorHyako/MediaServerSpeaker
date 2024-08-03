#include "SocketList.hpp"

using namespace Mss::Backend::Network;

bool SocketList::add(Wor::Network::EndPoint endPoint) noexcept {
    auto socket = std::make_shared<Wor::Network::TcpSocket>();
    socket->destinationEndPoint(std::move(endPoint));
    /**
     * TODO: Change to ping method
     */
    if (!socket->tryToConnect()) {
        return false;
    }
    socket->closeConnection();
    _socketList.emplace_back(std::move(socket));
    return true;
}

void SocketList::remove(std::uint8_t idx) noexcept {
    if (idx >= _socketList.size()) {
        _socketList.erase(std::begin(_socketList) + idx);
    }
}

void SocketList::clear() noexcept {
    _socketList.clear();
}

std::shared_ptr<Wor::Network::TcpSocket> SocketList::get(std::uint8_t idx) const noexcept {
    return idx < _socketList.size() ? _socketList[idx] : nullptr;
}
