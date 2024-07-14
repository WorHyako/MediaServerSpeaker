#pragma once

#include <string>
#include <vector>

#include "Command/ICommand.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author
     */
    class IControl {
    public:
        /**
         * @brief Dtor.
         */
        virtual ~IControl() = default;

        /**
         * @brief
         *
         * @param text
         */
        virtual void setText(std::string text) noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        virtual std::string getText() const noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        virtual const Backend::Command::ICommand* getCommand() const noexcept = 0;

        /**
         * @brief
         *
         * @param command
         */
        virtual void setCommand(Backend::Command::ICommand* command) noexcept = 0;
    };
}
