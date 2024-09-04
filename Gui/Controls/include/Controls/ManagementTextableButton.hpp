#pragma once

#include "Interfaces/IMovableControl.hpp"

class QLineEdit;

class QPushButton;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ManagementTextableButton final
            : public IMovableControl {
    Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit ManagementTextableButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ManagementTextableButton() override = default;

	private:
		QLineEdit *_textEdit;

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

	public slots:
		void commandChanged() noexcept override;

#pragma endregion Callbacks
	};
}
