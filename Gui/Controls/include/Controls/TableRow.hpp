#pragma once

#include <QWidget>

namespace Mss::Gui::Controls {

	/**
	 * @brief	Object represent row item for @code Table @endcode.
	 *			<p>
	 *			Row repeat @code CommandItem @endcode view.
	 *
	 * @author	WorHyako
	 */
	class TableRow final
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	keyValue	Key-value.
		 *
		 * @param	parent		Parent widget.
		 */
		explicit TableRow(const QPair<QString, QString> &keyValue = {}, QWidget *parent = nullptr);

		/**
		 * @brief	Dtor.
		 */
		~TableRow() override = default;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Key-value accessor.
		 *
		 * @return	Key-value.
		 */
		[[nodiscard]]
		QPair<QString, QString> keyValue() const noexcept;

		/**
		 * @brief	Key-value mutator.
		 *
		 * @param	keyValue New key-value.
		 */
		void keyValue(const QPair<QString, QString> &keyValue) noexcept;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

	signals:
		/**
		 * @brief	Signal to @code Table @endcode with data of modified kay-value
		 *
		 * @param	keyValue	Modified key-value.
		 *
		 * @param	sender		Self-pointer to identify modified row.
		 */
		void keyValueChanged(QPair<QString, QString> keyValue, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks

	};
}
