#pragma once

#include "Interfaces/IScope.hpp"

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButtonScope
            : public IScope {
    Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit QuickButtonScope(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickButtonScope() override = default;

    private:

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

        /**
         * @brief
         *
         * @param idx
         */
        void moveAllLeftSince(std::uint8_t idx) noexcept;

        std::uint8_t _buttonsCount;

#pragma region Callbacks
    public slots:

        /**
         * @brief
         *
         * @param toggled
         */
        void editModeChange(bool toggled);

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) noexcept override;

#pragma endregion Callbacks
    };
}
