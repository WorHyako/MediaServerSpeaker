#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

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
		void midiKeyPressed(std::uint8_t midiKeyIdx);

#pragma endregion Callbacks
	};

}
