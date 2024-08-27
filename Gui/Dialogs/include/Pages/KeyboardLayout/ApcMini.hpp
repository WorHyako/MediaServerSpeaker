#pragma once

#include "Pages/KeyboardLayout/BaseMidiLayout.hpp"

namespace Mss::Gui::Dialogs::Pages::KeyboardLayout {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ApcMini
			: public BaseMidiLayout {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit ApcMini(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ApcMini() noexcept override = default;
	};
}
