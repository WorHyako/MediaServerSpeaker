#pragma once

#include "Interfaces/IScope.hpp"

#include <QWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementScope final
            : public IScope {
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
        void removeAllControls() noexcept override;

        /**
         * @brief
         */
        void loadControls() noexcept override;

        /**
         * @brief
         */
        void saveControls() noexcept override;

#pragma region Callbacks
    public slots:

        /**
         * @brief
         *
         * @param toggled
         */
        void editModeChange(bool toggled);

    public:
        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) noexcept override;

#pragma endregion Callbacks
    };
}
