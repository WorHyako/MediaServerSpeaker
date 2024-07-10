#pragma once

#include "ICommand.hpp"

#include "pugixml.hpp"

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ActionCommand
            : public ICommand {
    public:
        /**
         * @brief Ctor.
         */
        ActionCommand() noexcept;

        /**
         * @brief
         *
         * @param socketName
         *
         * @return
         */
        [[nodiscard]]
        bool execute(std::string socketName) const noexcept override;

        /**
         * @brief
         */
        void clean() noexcept override;

        /**
         * @brief
         */
        void markCommandTag() noexcept override;

        /**
         * @brief
         *
         * @param item
         */
        void addItem(CommandItem item) noexcept override;

        /**
         * @brief
         *
         * @param item
         */
        void removeItem(CommandItem item) noexcept override;

        /**
         * @brief
         *
         * @param key
         */
        void removeItem(std::string key) noexcept override;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string str() const noexcept override;

    private:
        pugi::xml_document _command;
    };
}
