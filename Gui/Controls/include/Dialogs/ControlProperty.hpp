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
	 * @brief
	 *
	 * @author WorHyako
	 */
	class ControlProperty
			: public QDialog {
		Q_OBJECT

	public:
		/**
		 * @brief Ctor.
		 *
		 * @param parent
		 */
		explicit ControlProperty(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ControlProperty() override = default;

	private:
		/**
		 * @brief
		 *
		 * @param item
		 */
		void addCommandItemHLayout(const Backend::Command::CommandItem &item = {}, bool unique = true) noexcept;

		/**
		 * @brief
		 *
		 * @param hLayout
		 */
		void removeCommandItemHLayout(QHBoxLayout *hLayout) noexcept;

		/**
		 * @brief
		 */
		void applyChanged() noexcept;

		Controls::IControl *_control;

		QVBoxLayout *_commandLayout;

		std::string _controlName;

		std::string _sessionName;

		std::uint8_t _midiButtonId;

		std::unique_ptr<Backend::Command::BaseCommand> _testCommand;

	public:
#pragma region Callbacks

	signals:
		/**
		 * @brief
		 *
		 * @param commandStr
		 */
		void fullCommandChanged(const QString &commandStr);

	public slots:
		/**
		 * @brief
		 *
		 * @param idx
		 *
		 * @param item
		 */
		void refreshCommand(std::uint16_t idx, const Backend::Command::CommandItem &item);

#pragma endregion Callbacks
	};
}
