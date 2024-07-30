#pragma once

#include <memory>

#include "Command/ICommand.hpp"

namespace Mss::Gui::Components {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class CommandComponent {
    public:
        /**
         * @brief Ctor.
         */
        CommandComponent() noexcept;

        /**
         * @brief Dtor.
         */
        virtual ~CommandComponent() = default;

    private:
        std::unique_ptr<Backend::Command::ICommand> _command;

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        const Backend::Command::ICommand *getCommand() const noexcept;

        /**
         * @brief
         *
         * @param command
         */
        void setCommand(Backend::Command::ICommand *command) noexcept;

#pragma endregion Accessors/Mutators
    };
}
