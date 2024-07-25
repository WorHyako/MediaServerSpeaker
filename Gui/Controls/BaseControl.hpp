#pragma once

#include <QWidget>

#include "Components/CommandComponent.hpp"

#include "ContextMenu/ControlContextMenu.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class BaseControl
            : public QWidget,
              public Components::CommandComponent {
    public:
        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;

    protected:
        /**
         * @brief Ctor.
         */
        explicit BaseControl(QWidget *parent) noexcept;

        /**
         * @brief Dtor.
         */
        ~BaseControl() override = default;

        std::unique_ptr<ContextMenu::ControlContextMenu> _menu;

    public:
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
