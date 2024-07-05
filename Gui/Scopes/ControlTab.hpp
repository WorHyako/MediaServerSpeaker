#pragma once

#include <QTabWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ControlTab
            : public QTabWidget {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ControlTab(QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~ControlTab() override = default;
    };
}
