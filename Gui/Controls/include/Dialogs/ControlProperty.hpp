#pragma once

#include <memory>

#include <QDialog>

#include "Command/BaseCommand.hpp"

class QVBoxLayout;

class QHBoxLayout;

namespace Mss::Gui::Controls {
	class IControl;
}

namespace Mss::Gui::Controls::Dialogs {
	/**
	 * @brief	Dialog to modify control's properties.
	 *			<p>
	 *			Contains temporary fields to not modify original controls before applying by "Apply" button.
	 *
	 * @author	WorHyako
	 */
	class ControlProperty final
			: public QDialog {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit ControlProperty(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~ControlProperty() override = default;

	private:
		/**
		 * @brief			Adds item to command layout with selected @code CommandItem @endcode data.
		 *
		 * @param item		Command item to add.
		 *
		 * @param unique	Should be item unique or not.
		 *					<p>
		 *					Uses when command already filled, but need to fill command layout.
		 */
		void addCommandItemHLayout(const Backend::Command::CommandItem &item = {}, bool unique = true) noexcept;

		/**
		 * @brief	Remove selected item from command layout.
		 *
		 * @param	hLayout	Item to delete.
		 */
		void removeCommandItemHLayout(QHBoxLayout *hLayout) noexcept;

		/**
		 * @brief	Original control to modify.
		 */
		Controls::IControl *_control;

		/**
		 * @brief	Layout with command items.
		 */
		QVBoxLayout *_commandLayout;

		/**
		 * @brief	Temporary control name field to save modified content.
		 */
		std::string _controlName;

		/**
		 * @brief	Temporary control session name field to save modified content.
		 */
		std::string _sessionName;

		/**
		 * @brief	Temporary control midi button id field to save modified content.
		 */
		std::uint8_t _midiButtonId;

		/**
		 * @brief	Temporary command to test it.
		 */
		std::unique_ptr<Backend::Command::BaseCommand> _testCommand;

	public:
#pragma region Callbacks

	signals:
		/**
		 * @brief
		 *
		 * TODO: looks like it's useless method
		 *
		 * @param	commandStr
		 */
		void fullCommandChanged(const QString &commandStr);

	public slots:
		/**
		 * @brief	Refresh full command field and fill command text field.
		 *
		 * @param	idx		Index of modified command item.
		 *
		 * @param	item	New command item.
		 */
		void refreshCommand(std::uint16_t idx, const Backend::Command::CommandItem &item);

		/**
		 * @brief	Apply all modified fields to selected controls.
		 */
		void applyChanged() noexcept;

#pragma endregion Callbacks
	};
}
