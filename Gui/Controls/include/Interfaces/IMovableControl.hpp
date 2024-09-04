#pragma once

#include "Interfaces/IControl.hpp"

#include "Components/WidgetTransformComponent.hpp"

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class IMovableControl
			: public IControl,
			  public Components::WidgetTransformComponent {
	public:
		/**
		 * @brief Ctor.
		 */
		explicit IMovableControl(QWidget *parent) noexcept;

		/**
		 * @brief Dtor.
		 */
		~IMovableControl() override = default;

		/**
		 * @brief
		 *
		 * @param enable
		 */
		void editMode(bool enable) noexcept override;

	public:
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
