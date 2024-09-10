#pragma once

#include "Interfaces/IControl.hpp"

class QLineEdit;

class QPushButton;

namespace Mss::Gui::Controls {
	/**
	 * @brief	Static control to management tasks. Uses only in @code QuickTittlesScope @endcode.
	 *			<p>
	 *			By default, has server road.
	 *
	 * @author	WorHyako
	 */
	class QuickTitle final
			: public IControl {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit QuickTitle(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~QuickTitle() override = default;

	private:
		/**
		 * @brief	Control's @code QLineEdit @endcode.
		 */
		QLineEdit *_textEdit;

		/**
		 * @brief	Control's @code QPushButton @endcode.
		 */
		QPushButton *_button;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Control's text mutator for @code QLineEdit @endcode.
		 *
		 * @param	text New text.
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief	Control's text accessor for @code QLineEdit @endcode.
		 *
		 * @return	Control's text from @code QLineEdit @endcode.
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
