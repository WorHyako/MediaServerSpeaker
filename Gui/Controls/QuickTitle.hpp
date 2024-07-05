#pragma once

#include "Controls/Button.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author
     */
    class QuickTitle
            : public Button {
Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickTitle(QWidget* parent = nullptr);
    };
}
