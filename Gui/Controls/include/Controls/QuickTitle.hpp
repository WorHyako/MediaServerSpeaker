#pragma once

#include "Interfaces/IControl.hpp"

class QLineEdit;

class QPushButton;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickTitle final
            : public IControl {
    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickTitle(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickTitle() override = default;

	private:
		QLineEdit *_textEdit;

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

		/**
		 * @brief
		 */
		void commandChanged() noexcept override;

#pragma endregion Callbacks

	};
}
