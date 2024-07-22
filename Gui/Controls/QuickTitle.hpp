#pragma once

#include "Controls/BaseControl.hpp"

#include <QWidget>

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickTitle
            : public BaseControl,
              public QWidget {
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
