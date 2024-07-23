#pragma once

#include "IScope.hpp"

#include <QWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementScope final
            : public QWidget,
              public IScope {
    Q_OBJECT

    public:
        /**
         * @brief Dtor.
         *
         * @param parent
         */
        explicit ManagementScope(QWidget *parent = nullptr) noexcept;

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

    public slots:

        /**
         * @brief
         *
         * @param control
         */
        void addControl(ControlType controlType) noexcept override;

        /**
         * @brief
         *
         * @param control
         */
        void addControl(QWidget *control) noexcept override;

        /**
         * @brief
         *
         * @param control
         */
        void removeControl(QWidget *control) noexcept override;

        /**
         * @brief
         */
        void loadControls() noexcept override;

        /**
         * @brief
         */
        void saveControls() noexcept override;
    };
}
