#pragma once

#include <QWidget>

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class TableRow
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param keyValue
		 *
		 * @param parent
		 */
		explicit TableRow(const QPair<QString, QString> &keyValue = {}, QWidget *parent = nullptr);

		/**
		 * @brief Dtor.
		 */
		~TableRow() override = default;

	signals:
		/**
		 * @brief
		 *
		 * @param keyValue
		 */
		void keyValueChanged(QPair<QString, QString> keyValue, TableRow *sender);

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		QPair<QString, QString> keyValue() const noexcept;

		/**
		 * @brief
		 *
		 * @param keyValue
		 */
		void keyValue(const QPair<QString, QString> &keyValue) noexcept;

#pragma endregion Accessors/Mutators

	};
}
