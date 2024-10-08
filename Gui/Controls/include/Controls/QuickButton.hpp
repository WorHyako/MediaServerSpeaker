#pragma once

#include "Interfaces/IControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButton final
            : public IControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickButton() override = default;

	private:
		QPushButton *_button;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param text
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		std::string text() const noexcept override;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

	public:
		/**
		 * @brief
		 *
		 * @param e
		 */
		void mouseMoveEvent(QMouseEvent *e) override;

		void commandChanged() noexcept override;

#pragma endregion Callbacks
	};
}
