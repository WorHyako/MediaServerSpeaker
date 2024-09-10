#pragma once

#include "Interfaces/IControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {
	/**
	 * @brief	Static control to management tasks. Uses only in @code QuickButtonScope @endcode.
	 *			<p>
	 *			By default, has server road.
	 *
	 * @author	WorHyako
	 */
	class QuickButton final
			: public IControl {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit QuickButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickButton() override = default;

	private:
		/**
		 * @brief	Control's @code QPushButton @endcode.
		 */
		QPushButton *_button;

	public:
#pragma region Accessors/Mutators
		/**
		 * @brief	Control's text mutator.
		 *
		 * @param	text New control's text.
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief	Control's text accessor.
		 *
		 * @return	Control's text.
		 */
		[[nodiscard]]
		std::string text() const noexcept override;

#pragma endregion Accessors/Mutators

	public:
#pragma region Callbacks

		/**
		 * @brief
		 */
		void commandChanged() noexcept override;

#pragma endregion Callbacks
	};
}
