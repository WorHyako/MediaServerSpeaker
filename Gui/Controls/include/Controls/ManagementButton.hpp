#pragma once

#include "Interfaces/IMovableControl.hpp"

class QPushButton;

namespace Mss::Gui::Controls {

	/**
	 * @brief
	 *
	 * @author	WorHyako
	 */
	class ManagementButton final
			: public IMovableControl {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit ManagementButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ManagementButton() override = default;

	private:
		QPushButton *_button;

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

#pragma endregion Callbacks

	};
}
