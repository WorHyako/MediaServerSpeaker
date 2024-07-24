#pragma once

#include <string>
#include <vector>

#include "CommandItem.hpp"

namespace Mss::Backend::Command {

    /**
     * TODO: make common shared pointer for same command from different controls
     */

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
         * @param commandStr
         */
        virtual void set(const std::string& commandStr) noexcept = 0;

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
         *
         * @param tag
         */
        virtual void markTag(std::string tag) noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        virtual std::string getTag() const noexcept = 0;

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
         * @param
         *
         * @param items
         */
        virtual void addItems(std::vector<CommandItem> items) noexcept = 0;

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

        /**
         * @brief
         *
         * @param idx
         */
        virtual void removeItem(std::uint16_t idx) noexcept = 0;

        /**
         * @brief
         */
        virtual void removeItem() noexcept = 0;

        /**
         * @brief
         *
         * @param item
         */
        virtual void changeItem(CommandItem item) noexcept = 0;

        /**
         * @brief
         *
         * @param idx
         *
         * @param item
         */
        virtual void changeItem(std::uint16_t idx, CommandItem item) noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        virtual std::vector<CommandItem> getItems() const noexcept = 0;

        /**
         * @brief
         *
         * @param key
         *
         * @return
         */
        [[nodiscard]]
        virtual std::int16_t indexOf(std::string key) const noexcept = 0;

//        virtual std::vector<CommandItem>::iterator& getItemRef() noexcept = 0;
    };
}
