#pragma once

#include "Interfaces/IScope.hpp"

namespace Mss::Gui::Scopes {
	/**
	 * @brief	Scope for @code QuickTitle @endcode controls.
	 *			<p>
	 *			Has methods to load/save controls.
	 *
	 * @author	WorHyako
	 */
	class QuickTitlesScope final
			: public IScope {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit QuickTitlesScope(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~QuickTitlesScope() override = default;

		/**
		 * @brief	Adds control to scope.
		 *
		 * @param	control New control.
		 */
		void addControl(QWidget *control) noexcept override;

		/**
		 * @brief	Removes control from scope.
		 *
		 * @param	control Control.
		 */
		void removeControl(QWidget *control) noexcept override;

		/**
		 * @brief	Removes all controls from scope.
		 */
		void removeAllControls() noexcept override;

		/**
		 * @brief	Loads controls data from config and generate it in scope.
		 */
		void loadControls() noexcept override;

		/**
		 * @brief	Save controls data to config.
		 */
		void saveControls() noexcept override;

#pragma region Callbacks

	public slots:
		/**
		 * @brief	Slot to handle tab signal, that edit mode was changed.
		 *
		 * @param	toggled	New edit mode value.
		 */
		void editModeChange(bool toggled);

#pragma endregion Callbacks

	};
}
