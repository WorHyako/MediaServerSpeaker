#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {
	/**
	 * @brief	Movable control to management tasks.
	 *			<p>
	 *			By default, has midi and server road.
	 *
	 * @author	WorHyako
	 */
	class ManagementButton final
			: public IMovableControl {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit ManagementButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~ManagementButton() override = default;

	private:
		/**
		 * @brief	Control's @code QPushButton @endcode.
		 */
		QPushButton *_button;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Central control's text mutator.
		 *
		 * @param	text New text.
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

#pragma region Callbacks

		/**
		 * TODO: is it useless??
		 *
		 * @brief
		 */
		void commandChanged() noexcept override;

#pragma endregion Callbacks

	};
}
