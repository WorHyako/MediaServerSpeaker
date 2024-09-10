#pragma once

#include <QWidget>

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	class BaseMidiButton;
}

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {

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
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit BaseMidiLayout(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~BaseMidiLayout() noexcept override = default;

	protected:
		std::vector<BaseMidiButton *> _midiButtons;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		const std::vector<BaseMidiButton *> &midiButtons() const noexcept;

#pragma endregion Accessors/Mutators

#pragma region Callbacks

	signals:
		/**
		 * @brief
		 *
		 * @param idx
		 */
		void midiKeyPressed(std::uint8_t idx);

#pragma endregion Callbacks
	};

}
