#pragma once

#include <utility>
#include <string>

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class CommandItem {
    public:
        /**
         * @brief
         *
         * @param key
         *
         * @param value
         */
        CommandItem(std::string key = {}, std::string value = {}) noexcept;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string key() const noexcept;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string value() const noexcept;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        bool empty() const noexcept;

    private:
        std::pair<std::string, std::string> _item;
    };
}
