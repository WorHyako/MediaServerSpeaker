#include "Interfaces/IScope.hpp"

#include "Interfaces/IControl.hpp"
#include "Menus/ScopeContextMenu.hpp"
#include "Creators/ControlCreator.hpp"

#include <QMouseEvent>
#include <QPainter>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

IScope::IScope(QWidget *parent) noexcept
	: QWidget(parent),
	  edit_mode_(false),
	  controls_type_(ControlType::None) {
}

void IScope::edit_mode_change(bool edit_mode, QObjectList children) noexcept {
	edit_mode_ = edit_mode;
	std::ranges::for_each(children,
						  [&edit_mode](QObject *each) {
							  auto child = dynamic_cast<IControl *>(each);
							  if (!child) {
								  return;
							  }
							  child->edit_mode(edit_mode);
						  });
}

void IScope::open_menu(QMouseEvent *e, ControlType controls_type) noexcept {
	auto menu = new Menus::ScopeContextMenu(ControlType::ManagementButton
											| ControlType::ManagementTextableButton
											| ControlType::Table,
											this);
	menu->popup(QWidget::mapToGlobal(e->pos()));
}

#pragma region Callbacks

void IScope::mousePressEvent(QMouseEvent *e) noexcept {
	if (e->button() == Qt::MouseButton::RightButton) {
		auto menu = new Menus::ScopeContextMenu(controls_type_, this);
		menu->popup(QWidget::mapToGlobal(e->pos()));
	}

	QWidget::mousePressEvent(e);
}

void IScope::paintEvent(QPaintEvent *e) noexcept {
	QPainter painter(this);
	painter.setPen(QColor(0xaa, 0xaa, 0xaa));
	painter.drawRoundedRect(0, 0, QWidget::width(), QWidget::height(), 5, 5);

	QWidget::paintEvent(e);
}

#pragma endregion Callbacks
