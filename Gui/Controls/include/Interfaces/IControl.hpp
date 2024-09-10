#pragma once

#include <QWidget>

#include "Components/CommandComponent.hpp"
#include "Components/MidiComponent.hpp"

namespace Mss::Gui::Controls {

	/**
	 * @brief	Abstract object for all wor controls. Names all control with "WorControl" name.
	 *			<p>
	 *			Adds @code CommandComponent @endcode and @code MidiComponent @endcode.
	 *
	 * @author	WorHyako
	 */
	class IControl
			: public QWidget,
			  public Components::CommandComponent,
			  public Components::MidiComponent {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 */
		explicit IControl(QWidget *parent) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~IControl() override = default;

		/**
		 * @brief	Creates server road.
		 *			<p>
		 *			Takes data from @code MidiComponent @endcode, @code CommandComponent @endcode
		 *			and registrar new road in @code MidiRoadMap @endcode if it possible.
		 */
		void createServerRoad() const noexcept;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Edit mode mutator.
		 *			<p>
		 *			Orient to calling only from wor scope objects.
		 *
		 * @param	enable	New edit mode value.
		 */
		virtual void editMode(bool enable) noexcept;

		/**
		 * @brief	Control's text mutator.
		 *
		 * @param	text New control's text.
		 */
		virtual void text(std::string text) noexcept = 0;

		/**
		 * @brief	Control's text accessor.
		 *
		 * @return	Control's text.
		 */
		[[nodiscard]]
		virtual std::string text() const noexcept = 0;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

		/**
		 * @brief	Mouse press event.
		 *			<p>
		 *			Left mouse uses for road going.
		 *			<p>
		 *			Right mouse uses for context menu calling.
		 *
		 * @param	e	Mouse event info.
		 */
		void mousePressEvent(QMouseEvent *e) override;

	public slots:
		/**
		 * @brief	Slot to handle event of command changing.
		 *			<p>
		 *			All children should to process event themselves to modify text fields.
		 */
		virtual void commandChanged() noexcept = 0;

		/**
		 * @brief	Painting event. Uses for style sheet applying.
		 *
		 * @param	e	Paint event.
		 */
		void paintEvent(QPaintEvent *e) override;

#pragma endregion Callbacks
	};
}
