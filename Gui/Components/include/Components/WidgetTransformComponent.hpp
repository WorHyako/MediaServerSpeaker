#pragma once

#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {
	/**
	 * @brief	Object to transform (move and resize) Qt Widgets.
	 *
	 * @usage
	 * @code
	 *			class Foo
	 *				: public QWidget,
	 *				  public Components::WidgetTransformComponent {
	 *			...
	 *
	 *			void Foo::mouseMoveEvent(QMouseEvent *e) {
	 *				Components::WidgetTransformComponent::doTransform(e);
	 *				...
	 *			}
	 *
	 *			void Foo::mouseReleaseEvent(QMouseEvent *e) {
	 *				Components::WidgetTransformComponent::stopTransform(e);
	 *				...
	 *			}
	 *
	 *			void Foo::enableTransforming(bool enable) noexcept {
	 *				Components::WidgetTransformComponent::canTransform(enable);
	 *				...
	 *		    }
	 * @endcode
	 *
	 * @author	WorHyako
	 */
	class WidgetTransformComponent {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit WidgetTransformComponent(QWidget* parent) noexcept;

		/**
		 * @brief Dtor.
		 */
		virtual ~WidgetTransformComponent() noexcept = default;

		/**
		 * @brief
		 *
		 * @param e
		 */
		void doTransform(QMouseEvent* e) noexcept;

		/**
		 * @brief
		 */
		void stopTransform() noexcept;

	private:
		QWidget* _parent;

		QPoint _lastMousePressPosition;

		bool _canTransform;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param canTransform
		 */
		void canTransform(bool canTransform) noexcept;

#pragma endregion Accessors/Mutators
	};
}
