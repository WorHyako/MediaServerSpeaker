#pragma once

#include "Interfaces/IScope.hpp"

#include <QMenu>

namespace Mss::Gui::Scopes::Menus {

	/**
	 * @brief
	 *
	 * @usage
	 * @code
	 *          auto menu = new ScopeContextMenu(ControlType::ManagementButton |
	 *                                           ControlType::Button,
	 *                                           parent);
	 * @endcode
	 *
	 * @author  WorHyako
	 */
	class ScopeContextMenu final
			: public QMenu {
	public:
		/**
		 * @brief Ctor.
		 *
		 * @param controlType
		 *
		 * @param parent
		 */
		explicit ScopeContextMenu(ControlType controlType, QWidget *parent = nullptr) noexcept;

		/**
		 * @brief Dtor.
		 */
		~ScopeContextMenu() override = default;
	};
}
