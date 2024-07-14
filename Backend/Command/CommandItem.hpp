#pragma once

#include <utility>
#include <string>

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class CommandItem final {
    public:
        /**
         * @brief Ctor.
         */
        CommandItem() noexcept = default;

        /**
         * @brief
         *
         * @param key
         *
         * @param value
         */
        CommandItem(std::string key, std::string value) noexcept;

        /**
         * @brief Copy ctor.
         */
        CommandItem(const CommandItem &) noexcept = default;

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
        std::string _key;

        std::string _value;
    };
}
