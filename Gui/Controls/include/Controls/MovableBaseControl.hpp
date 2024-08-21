#pragma once

#include "BaseControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class MovableBaseControl
			: public BaseControl,
			  public Components::WidgetTransformComponent {
	public:
		/**
		 * @brief Ctor.
		 */
		explicit MovableBaseControl(QWidget *parent) noexcept;

		/**
		 * @brief Dtor.
		 */
		~MovableBaseControl() override = default;

		/**
		 * @brief
		 *
		 * @param enable
		 */
		void editMode(bool enable) noexcept;

#pragma region Callbacks

	public:
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
