#pragma once

#include <memory>
#include <string>

#include "CommandItem.hpp"

namespace Wor::Network {
    class TcpSocket;
}

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ICommand {
    public:
        /**
         * @brief Dtor.
         */
        virtual ~ICommand() = default;

        /**
         * @brief
         *
         * @param socketName
         *
         * @return
         */
        [[nodiscard]]
        virtual bool execute(std::string socketName) const noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        virtual std::string str() const noexcept = 0;

        /**
         * @brief
         */
        virtual void markCommandTag() noexcept = 0;

        /**
         * @brief
         */
        virtual void clean() noexcept = 0;

        /**
         * @brief
         *
         * @param item
         */
        virtual void addItem(CommandItem item) noexcept = 0;

        /**
         * @brief
         *
         * @param item
         */
        virtual void removeItem(CommandItem item) noexcept = 0;

        /**
         * @brief
         *
         * @param key
         */
        virtual void removeItem(std::string key) noexcept = 0;
    };
}
