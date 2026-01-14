module;

#include "CommandItem.hpp"

export module mss.backend:command.CommandBuilder;

import std;

namespace Mss::Backend::Command {
/**
 * @brief Object to create commands and log process.
 *
 * @usage
 * @code
 *     CommandBuilder<BaseCommand>::build();
 * @endcode
 *
 * @tparam TCommandType Command class type
 *
 * @author WorHyako
 */
export template <class TCommandType>
class CommandBuilder final {
  public:
    /**
     * @brief Constructor (deleted).
     *
     * This class contains only static methods and should not be instantiated.
     */
    CommandBuilder() noexcept = delete;

    /**
     * @brief Creates command from selected CommandItems.
     *
     * @param items List of CommandItems to create command.
     *
     * @return Unique pointer of created command.
     *
     * @see CommandItem
     */
    [[nodiscard]]
    static std::unique_ptr<TCommandType> build(std::vector<CommandItem> items = {}) noexcept;

    /**
     * @brief Logs command building process.
     *
     * @warning Not ready yet.
     *
     * @deprecated This method is not implemented yet.
     */
    [[deprecated]]
    static void log() noexcept;
};

template <class TCommandType>
std::unique_ptr<TCommandType> CommandBuilder<TCommandType>::build(std::vector<CommandItem> items) noexcept {
    std::unique_ptr<TCommandType> command{ new TCommandType };
    std::ranges::for_each(items, [&command](const auto &each) {
        command->add_item(std::move(each));
    });
    return command;
}

template <class CommandType>
void CommandBuilder<CommandType>::log() noexcept {
}
}
