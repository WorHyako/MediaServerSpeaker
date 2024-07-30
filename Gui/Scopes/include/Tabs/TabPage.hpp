#pragma once

#include <QWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class TabPage
            : public QWidget {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit TabPage(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~TabPage() override = default;

    public slots:

        /**
         * @brief
         *
         * @param toggled
         */
        void editModeChange(bool toggled);

    signals:

        /**
         * @brief
         *
         * @param toggled
         */
        void editModeChanged(bool toggled);
    };
}
