#pragma once

#include <QWidget>

class QGridLayout;

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementScope
            : public QWidget {
    Q_OBJECT

    public:
        /**
         * @brief Dtor.
         *
         * @param parent
         */
        explicit ManagementScope(QWidget* parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~ManagementScope() override = default;

        /**
         * @brief
         *
         * @param e
         */
        void paintEvent(QPaintEvent *e) override;

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;

    private:
        QGridLayout* _layout;
    };
}
