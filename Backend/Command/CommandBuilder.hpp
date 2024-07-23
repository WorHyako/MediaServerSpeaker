#pragma once

#include <vector>

#include "CommandItem.hpp"
#include "ICommand.hpp"

namespace Mss::Backend::Command {

    /**
     * @brief
     *
     * @tparam TCommandType
     *
     * @author WorHyako
     */
    template<class TCommandType>
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
        static std::unique_ptr<TCommandType> build(std::vector<CommandItem> items = {}) noexcept;

        /**
         * @brief
         */
        static void log() noexcept;
    };

    template<class TCommandType>
    std::unique_ptr<TCommandType> CommandBuilder<TCommandType>::build(std::vector<CommandItem> items) noexcept {
        std::unique_ptr<TCommandType> command(new TCommandType);
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


