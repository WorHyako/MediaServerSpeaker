#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ApcMini
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit ApcMini(QWidget *parent = nullptr) noexcept;

#pragma region Accessors/Mutators

#pragma endregion Accessors/Mutators

#pragma region Callbacks

	signals:
		void midiKeyPressed(std::uint8_t midiKeyIdx);

#pragma endregion Callbacks
	};
}
