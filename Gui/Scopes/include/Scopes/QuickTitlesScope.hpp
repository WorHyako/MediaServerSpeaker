#pragma once

#include "Interfaces/IScope.hpp"

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author
     */
    class QuickTitlesScope
            : public IScope {
    Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit QuickTitlesScope(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickTitlesScope() override = default;

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
