#pragma once

#include <QTabWidget>

namespace Mss::Gui::Scopes {
	/**
	 * @brief	Widget to manage working space's tabs.
	 *
	 * @author	WorHyako
	 *
	 * @see		@code TabPage @endcode
	 */
	class ControlTab final
			: public QTabWidget {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit ControlTab(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ControlTab() override = default;

	signals:
		/**
		 * @brief	Signal to notify all scopes about edit mode changing.
		 *
		 * @param	toggled	New edit mode value.
		 */
		void editModeChanged(bool toggled);
	};
}
