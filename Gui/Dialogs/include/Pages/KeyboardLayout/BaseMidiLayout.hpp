#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	class BaseMidiButton;
}

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	class BaseMidiButton;

	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class BaseMidiLayout
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit BaseMidiLayout(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~BaseMidiLayout() noexcept override = default;

#pragma region Callbacks

	signals:
		/**
		 * @brief
		 *
		 * @param midiKeyIdx
		 */
		void midiKeyPressed(Mss::Gui::Dialogs::Pages::KeyboardLayout::BaseMidiButton* midiKeyIdx);

#pragma endregion Callbacks
	};

}
