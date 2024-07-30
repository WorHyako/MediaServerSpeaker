#pragma once

#include <QTabWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ControlTab final
            : public QTabWidget {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ControlTab(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~ControlTab() override = default;
    };
}
