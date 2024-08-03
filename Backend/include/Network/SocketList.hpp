#pragma once

#include <vector>
#include <memory>

#include "WorLibrary/Network/TcpSocket.hpp"

namespace Mss::Backend::Network {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class SocketList {
    public:
        /**
         * @brief Dtor.
         */
        virtual ~SocketList() = default;

        /**
         * @brief
         *
         * @param endPoint
         *
         * @param socketIndex
         *
         * @return
         */
        [[nodiscard]]
        bool add(Wor::Network::EndPoint endPoint) noexcept;

        /**
         * @brief
         *
         * @param socketIndex
         */
        void remove(std::uint8_t idx) noexcept;

        /**
         * @brief
         */
        void clear() noexcept;

        /**
         * @brief
         *
         * @param socketIndex
         *
         * @return
         */
        [[nodiscard]]
        std::shared_ptr<Wor::Network::TcpSocket> get(std::uint8_t socketIndex) const noexcept;

    private:
        std::vector<std::shared_ptr<Wor::Network::TcpSocket>> _socketList;
    };
}
