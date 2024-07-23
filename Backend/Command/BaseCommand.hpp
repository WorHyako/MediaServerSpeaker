#pragma once

#include "ICommand.hpp"

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @author
     */
    class BaseCommand
            : public ICommand {
    public:
        /**
         * @brief Dtor.
         */
        ~BaseCommand() override = default;

        /**
         * @brief
         *
         * @param item
         */
        void addItem(CommandItem item) noexcept override;

        /**
         * @brief
         *
         * @param items
         */
        void addItems(std::vector<CommandItem> items) noexcept override;

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
         * @param idx
         */
        void removeItem(std::uint16_t idx) noexcept override;

        /**
         * @brief
         */
        void removeItem() noexcept override;

        /**
         * @brief
         */
        void clean() noexcept override;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string str() const noexcept override;

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
         *
         * @return
         */
        [[nodiscard]]
        std::string getTag() const noexcept override;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::vector<CommandItem> getItems() const noexcept override;

        /**
         * @brief
         *
         * @param item
         */
        void changeItem(CommandItem item) noexcept override;

        /**
         * @brief
         *
         * @param idx
         *
         * @param item
         */
        void changeItem(std::uint16_t idx, CommandItem item) noexcept override;

        /**
         * @brief
         *
         * @param tag
         */
        void markTag(std::string tag) noexcept override;

        /**
         * @brief
         *
         * @param key
         *
         * @return
         */
        [[nodiscard]]
        std::int16_t indexOf(std::string key) const noexcept override;

    protected:

        std::string _tag;

        std::vector<CommandItem> _items;
    };
}
