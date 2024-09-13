#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Controls {
	class TableRow;
}

namespace Mss::Gui::Controls {
	/**
	 * @brief	Movable control to management tasks.
	 *			<p>
	 *			By default, has midi and server road.
	 *
	 * @author	WorHyako
	 */
	class Table final
			: public IMovableControl {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit Table(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~Table() override = default;

		/**
		 * @brief	Adds row to the end.
		 */
		void addRow(const QPair<QString, QString> &pair = {}) noexcept;

		/**
		 * @brief	Remove the last row.
		 */
		void removeRow() noexcept;

		/**
		 * @brief	Clear all rows.
		 */
		void clear() noexcept;

	private:
		/**
		 * @brief	Control's @code QPushButton @endcode.
		 */
		QPushButton *_button;

		/**
		 * @brief	Layout with @code TableRow @endcode.
		 */
		QVBoxLayout *_rowsLayout;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Control's text mutator for @code QPushButton @endcode.
		 *
		 * @param	text New text.
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief	Control's text accessor for @code QPushButton @endcode.
		 *
		 * @return	Control's text.
		 */
		[[nodiscard]]
		std::string text() const noexcept override;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

		/**
		 * @brief
		 */
		void commandChanged() noexcept override;

	public slots:
		/**
		 * @brief	Slot to handle signals from @code TableRow @endcode.
		 *
		 * @param	keyValue	Modified key-value. TODO: useless, i guess.
		 *
		 * @param	sender		Modified row pointer.
		 */
		void keyValueChange(const QPair<QString, QString> &keyValue, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks

	};
}
