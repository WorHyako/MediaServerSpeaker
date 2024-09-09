#pragma once

#include <QWidget>

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class TableRow final
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

#pragma region Callbacks

	signals:
		/**
		 * @brief
		 *
		 * @param keyValue
		 */
		void keyValueChanged(QPair<QString, QString> keyValue, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks

	};
}
