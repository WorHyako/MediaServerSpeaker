#pragma once

#include <string>
#include <vector>

#include <QPoint>

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

    public:
#pragma region Accessors/Mutators

        /**
         * @brief
         *
         * @return
         */
//        [[nodiscard]]
//        virtual bool getCanMove() const noexcept = 0;

        /**
         * @brief
         *
         * @param canMove
         */
//        virtual void setCanMove(bool canMove) noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
//        [[nodiscard]]
//        virtual bool getCanResize() const noexcept = 0;

        /**
         * @brief
         *
         * @param canResize
         */
//        virtual void setCanResize(bool canResize) noexcept = 0;

        /**
         * @brief
         *
         * @return
         */
//        [[nodiscard]]
//        virtual QPoint getPosition() const noexcept = 0;

        /**
         * @brief
         *
         * @param position
         */
//        virtual void setPosition(QPoint position) noexcept = 0;

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
        virtual const Backend::Command::ICommand *getCommand() const noexcept = 0;

        /**
         * @brief
         *
         * @param command
         */
        virtual void setCommand(Backend::Command::ICommand *command) noexcept = 0;

#pragma endregion Accessors/Mutators

    };
}
