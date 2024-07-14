#pragma once

#include <vector>

#include "CommandItem.hpp"
#include "ICommand.hpp"

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @tparam CommandType
     *
     * @author WorHyako
     */
    template<class CommandType>
    class CommandBuilder {
    public:
        /**
         * @brief Ctor.
         */
        CommandBuilder() noexcept = delete;

        /**
         * @brief
         *
         * @param items
         *
         * @return
         */
        [[nodiscard]]
        static std::unique_ptr<CommandType> build(std::vector<CommandItem> items = {}) noexcept;

        /**
         * @brief
         */
        static void log() noexcept;
    };

    template<class CommandType>
    std::unique_ptr<CommandType> CommandBuilder<CommandType>::build(std::vector<CommandItem> items) noexcept {
        std::unique_ptr<CommandType> command(new CommandType);
        std::for_each(std::begin(items), std::end(items), [&command](const auto &each) {
            command->addItem(std::move(each));
        });
        log();
        return command;
    }

    template<class CommandType>
    void CommandBuilder<CommandType>::log() noexcept {

    }
}


