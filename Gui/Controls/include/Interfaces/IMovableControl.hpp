#pragma once

#include "Interfaces/IControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

	/**
	 * @brief	Abstract object for all movable wor control.
	 *			<p>
	 *			Adds @code WidgetTransfromComponent @endcode.
	 *
	 * @author WorHyako
	 */
	class IMovableControl
			: public IControl,
			  public Components::WidgetTransformComponent {
	public:
		/**
		 * @brief	Ctor.
		 */
		explicit IMovableControl(QWidget *parent) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~IMovableControl() override = default;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Edit mode mutator.
		 *			<p>
		 *			Orient to calling only from wor scope objects.
		 *
		 * @param	enable	New edit mode value.
		 */
		void editMode(bool enable) noexcept override;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

		/**
		 * @brief
		 *
		 * @param e
		 */
		void mouseMoveEvent(QMouseEvent *e) override;

		/**
		 * @brief
		 *
		 * @param e
		 */
		void mouseReleaseEvent(QMouseEvent *e) override;

#pragma endregion Callbacks
	};
}
