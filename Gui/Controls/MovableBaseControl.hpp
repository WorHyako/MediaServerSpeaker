#pragma once

#include "BaseControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class MovableBaseControl
            : public BaseControl,
              public Components::WidgetTransformComponent {
    public:
        /**
         * @brief Ctor.
         */
        explicit MovableBaseControl(QWidget *parent) noexcept;
    };
}