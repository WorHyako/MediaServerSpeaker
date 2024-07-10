#pragma once

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author
     */
    class IControl {
    public:
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
        virtual std::string getCommand() const noexcept = 0;

        /**
         * @brief
         *
         * @param command
         */
        virtual void setCommand(std::string command) noexcept = 0;
    };
}
