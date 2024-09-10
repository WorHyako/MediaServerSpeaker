#pragma once

#include <cstdint>

#include <QWidget>

namespace Mss::Gui::Scopes {
	/**
	 * @brief	Contains list of controls, that uses for @code ContextMenu @endcode filling.
	 *
	 * @author	WorHyako
	 */
	enum class ControlType
			: std::uint8_t {
		/**
		 * No control
		 */
		None = 0b0,

		/**
		 * @see @code Gui::Controls::ManagementTextableButton @endcode
		 */
		ManagementTextableButton = 0b1,

		/**
		 * @see @code Gui::Controls::ManagementButton @endcode
		 */
		ManagementButton = 0b10,

		/**
		 * @see	@code Gui::Controls::QuickButton @endcode
		 */
		QuickButton = 0b100,

		/**
		 * @see	@code Gui::Controls::QuickTitle @endcode
		 */
		QuickTitle = 0b1000,

		/**
		 * @see	@code Gui::Controls::Table @endcode
		 */
		Table = 0b10000
	};

	/**
	 * @brief	Operator
	 *
	 * @param	lhs	Left hand side object.
	 *
	 * @param	rhs	Right hand side object.
	 *
	 * @return
	 *
	 * @author	WorHyako
	 */
	[[nodiscard]]
	inline ControlType operator|(ControlType lhs, ControlType rhs) {
		return static_cast<ControlType>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	/**
	 * @brief
	 *
	 * @param	lhs	Left hand side object.
	 *
	 * @param	rhs Right hand side object.
	 *
	 * @return
	 *
	 * @author	WorHyako
	 */
	[[nodiscard]]
	inline bool operator&(ControlType lhs, ControlType rhs) {
		return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

	/**
	 * @brief	Abstract class for all scopes. Dictates main methods for scope's behaviour.
	 *
	 * @author	WorHyako
	 */
	class IScope
			: public QWidget {
		Q_OBJECT

	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	parent	Parent widget.
		 */
		explicit IScope(QWidget *parent = nullptr) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~IScope() noexcept override = default;

		/**
		 * @brief	Adds control to scope.
		 *
		 * @param	control New control.
		 */
		virtual void addControl(QWidget *control) noexcept = 0;

		/**
		 * @brief	Removes control from scope.
		 *
		 * @param	control Control.
		 */
		virtual void removeControl(QWidget *control) noexcept = 0;

		/**
		 * @brief	Removes all controls from scope.
		 */
		virtual void removeAllControls() noexcept = 0;

		/**
		 * @brief	Loads control from config.
		 */
		virtual void loadControls() noexcept = 0;

		/**
		 * @brief	Save controls to config.
		 */
		virtual void saveControls() noexcept = 0;

	protected:
		/**
		 * @brief	Working mode, when it's available to change control's properties and settings
		 *			<p>
		 *			Edit mode is controlling by @code MainWindow @endcode
		 */
		bool _editMode;

		/**
		 * @brief	Available controls for current scope.
		 */
		ControlType _controlsType;

		/**
		 * TODO: i don't know, what this method do...
		 *
		 * @brief
		 *
		 * @param children
		 */
		virtual void editModeChange(bool editMode, QObjectList children) noexcept;

		/**
		 * @brief	Opens menu with list of available list of controls.
		 *
		 * @param	controlsType Available controls.
		 */
		virtual void openMenu(QMouseEvent *e, ControlType controlsType) noexcept;

#pragma region Callbacks

		/**
		 * @brief	Mouse press event. Uses for context menu calling.
		 *
		 * @param	e	Mouse event info.
		 */
		void mousePressEvent(QMouseEvent *e) noexcept override;

		/**
		 * @brief	Painting event. Uses for style sheet applying.
		 *
		 * @param	e	Paint event.
		 */
		void paintEvent(QPaintEvent *e) noexcept override;

#pragma endregion Callbacks
	};
}
