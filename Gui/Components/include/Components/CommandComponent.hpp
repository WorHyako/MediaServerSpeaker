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
        virtual ~CommandComponent() noexcept = default;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        bool execute() const noexcept;

    private:
        std::unique_ptr<Backend::Command::ICommand> _command;

        std::string _sessionName;

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        Backend::Command::ICommand *command() const noexcept;

        /**
         * @brief
         *
         * @param command
         */
        void command(Backend::Command::ICommand *command) noexcept;

        /**
         * @brief
         *
         * @param sessionName
         */
        void sessionName(std::string sessionName) noexcept;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        std::string sessionName() const noexcept;

#pragma endregion Accessors/Mutators
    };
}
