#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

class QVBoxLayout;

namespace Mss::Gui::Controls {
	class TableRow;
}

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class Table final
			: public IMovableControl {
		Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit Table(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~Table() override = default;

		/**
		 * @brief
		 */
		void addRow(const QPair<QString, QString> &pair = {}) noexcept;

		/**
		 * @brief
		 */
		void removeRow() noexcept;

		/**
		 * @brief
		 */
		void clear() noexcept;

	private:
		QPushButton *_button;

		QVBoxLayout *_rowsLayout;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param text
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief
		 *
		 * @return
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
		 * @brief
		 *
		 * @param keyValue
		 */
		void keyValueChange(const QPair<QString, QString> &keyValue, Mss::Gui::Controls::TableRow *sender);

#pragma endregion Callbacks

	};
}
