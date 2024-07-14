#pragma once

#include "IControl.hpp"

#include "Command/ICommand.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class BaseControl
            : public IControl {
    protected:
        /**
         * @brief Ctor.
         */
        BaseControl() = default;

    public:
        /**
         * @brief Dtor.
         */
        ~BaseControl() override = default;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        const Backend::Command::ICommand* getCommand() const noexcept override;

        /**
         *
         * @param command
         */
        void setCommand(Backend::Command::ICommand* command) noexcept override;

    protected:
        std::unique_ptr<Backend::Command::ICommand> _command;
    };
}
