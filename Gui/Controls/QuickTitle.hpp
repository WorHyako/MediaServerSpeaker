#pragma once

#include "Controls/Button.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickTitle
            : public Button {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickTitle(QWidget* parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~QuickTitle() override = default;
    };
}
