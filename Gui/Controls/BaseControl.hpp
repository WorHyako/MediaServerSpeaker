#pragma once

#include <QWidget>

#include "Command/ICommand.hpp"

#include "Components/CommandComponent.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class BaseControl
            : public QWidget,
              public Components::CommandComponent {
    protected:
        /**
         * @brief Ctor.
         */
        explicit BaseControl(QWidget *parent) noexcept;

    public:
        /**
         * @brief Dtor.
         */
        ~BaseControl() override = default;

#pragma endregion Accessors/Mutators

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

#pragma endregion Accessors/Mutators

    };
}
