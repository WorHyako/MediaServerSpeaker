#pragma once

#include "BaseCommand.hpp"

namespace Mss::Backend::Command {

    template<class CommandType>
    class CommandBuilder;

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ActionCommand final
            : public BaseCommand {
    public:
        /**
         * @brief Dtor.
         */
        ~ActionCommand() override = default;

    protected:
        /**
         * @brief Ctor.
         */
        ActionCommand() noexcept = default;

    public:
        friend CommandBuilder<ActionCommand>;
    };
}
