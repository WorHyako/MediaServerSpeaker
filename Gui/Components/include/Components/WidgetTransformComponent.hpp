#pragma once

#include <QPoint>

class QWidget;

class QMouseEvent;

namespace Mss::Gui::Components {
	/**
	 * @brief	Object to transform (move and resize) Qt Widgets.
	 *			<p>
	 *			Orients just for inheritance existing.
	 *			<p>
	 *			Does resize with Alt modifier.
	 *			<p>
	 *			Does move with Ctrl modifier.
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
		 * @brief	Ctor.
		 *
		 * @param	parent	Object to transform.
		 */
		explicit WidgetTransformComponent(QWidget* parent) noexcept;

		/**
		 * @brief	Dtor.
		 */
		virtual ~WidgetTransformComponent() noexcept = default;

		/**
		 * @brief	Does transform in case of pressed modifier (See class description).
		 *
		 * @param	e	Mouse event to take ket modifiers and position.
		 */
		void doTransform(QMouseEvent* e) noexcept;

		/**
		 * @brief	Resets last mouse position.
		 */
		void stopTransform() noexcept;

	private:
		QWidget* _parent;

		QPoint _lastMousePressPosition;

		bool _canTransform;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Accessor for transforming flag.
		 *
		 * @param	canTransform	New Value
		 */
		void canTransform(bool canTransform) noexcept;

#pragma endregion Accessors/Mutators
	};
}
