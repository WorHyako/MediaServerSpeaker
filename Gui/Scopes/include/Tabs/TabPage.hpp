#pragma once

#include <QWidget>

namespace Mss::Gui::Scopes {
	/**
	 * @brief	Tab page for working space. Contains @code QuickTitlesScope @endcode,
	 *			@code QuickButtonScope @endcode, @code ManagementScope @endcode
	 *
	 * @author	WorHyako
	 *
	 * @see		@code ControlTab @endcode
	 */
	class TabPage final
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit TabPage(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~TabPage() override = default;

	public slots:
		/**
		 * @brief	Slot to handle tab signal, that edit mode was changed.
		 *
		 * @param	toggled	New edit mode value.
		 */
		void editModeChange(bool toggled);

	signals:
		/**
		 * @brief	Signal to notify all scopes about edit mode changing.
		 *
		 * @param	toggled	New edit mode value.
		 */
		void editModeChanged(bool toggled);
	};
}
