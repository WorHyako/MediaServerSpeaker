#pragma once

#include "Interfaces/IScope.hpp"

namespace Mss::Gui::Scopes {
	/**
	 * @brief	Scope for @code QuickButton @endcode controls.
	 *			<p>
	 *			Has strange layout architecture cause of author's low Qt skills.
	 *			@code
	 *			| + + + + + + |
	 *			| + + + + + + |
	 *			| + + + + + + |
	 *			| + + + + + + |
	 *			| + + + + + + |
	 *			@endcode
	 *			Each grid's cell fills with empty hidden @code QWidget @endcode to keep grid
	 *			in correct indexing and size.
	 *			There is a swap operation between @code QuickButton @endcode and @code QWidget @endcode
	 *			when u add or remove control.
	 *			I will be rework this moment, when find a good way to keep table-like grid view.
	 *
	 * @author	WorHyako
	 */
	class QuickButtonScope final
			: public IScope {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent Parent widget.
		 */
		explicit QuickButtonScope(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~QuickButtonScope() override = default;

	private:
		/**
		 * @brief	Adds control to the end of scope's active buttons list.
		 *
		 * @param	control New control.
		 */
		void addControl(QWidget *control) noexcept override;

		/**
		 * @brief	Removes control from scope. Moves all control to keep at a row-like view.
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

		/**
		 * @brief	Move all controls to left, when some of them was removed.
		 *
		 * @param	idx Start cell index.
		 */
		void moveAllLeftSince(std::uint8_t idx) noexcept;

		/**
		 * @brief	Number of active controls.
		 */
		std::uint8_t _buttonsCount;

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
