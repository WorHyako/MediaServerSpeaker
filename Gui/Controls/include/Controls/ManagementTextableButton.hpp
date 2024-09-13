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
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit ManagementTextableButton(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~ManagementTextableButton() override = default;

    private:
    	/**
		 * @brief	Control's @code QLineEdit @endcode.
		 */
		QLineEdit *_textEdit;

    	/**
		 * @brief	Control's @code QPushButton @endcode.
		 */
		QPushButton *_button;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Control's text mutator for @code QLineEdit @endcode.
		 *
		 * @param	text
		 */
		void text(std::string text) noexcept override;

		/**
		 * @brief	Control's text accessor for @code QLineEdit @endcode.
		 *
		 * @return	Control's text.
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
