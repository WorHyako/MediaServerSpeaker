#pragma once

#include <QStackedWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author
     */
    class QuickTitlesScope
            : public QStackedWidget {
Q_OBJECT
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickTitlesScope(QWidget* parent = nullptr);

        /**
         * @brief
         *
         * @param e
         */
        void paintEvent(QPaintEvent *e) override;
    };
}