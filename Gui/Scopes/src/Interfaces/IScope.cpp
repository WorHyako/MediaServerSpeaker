#include "Interfaces/IScope.hpp"

#include "Interfaces/IControl.hpp"
#include "Menus/ScopeContextMenu.hpp"

#include <QMouseEvent>
#include <QPainter>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

IScope::IScope(QWidget *parent) noexcept
	: QWidget(parent),
	  _editMode(false),
	  _controlsType(ControlType::None) {
}

void IScope::editModeChange(bool editMode, QObjectList children) noexcept {
	_editMode = editMode;
	std::ranges::for_each(children,
						  [&editMode](QObject *each) {
							  auto child = dynamic_cast<IControl *>(each);
							  if (!child) {
								  return;
							  }
							  child->editMode(editMode);
						  });
}

void IScope::openMenu(QMouseEvent *e, ControlType controlsType) noexcept {
	auto menu = new Menus::ScopeContextMenu(ControlType::ManagementButton
											| ControlType::ManagementTextableButton
											| ControlType::Table,
											this);
	menu->popup(QWidget::mapToGlobal(e->pos()));
}

#pragma region Callbacks

void IScope::mousePressEvent(QMouseEvent *e) noexcept {
	if (e->button() == Qt::MouseButton::RightButton) {
		auto menu = new Menus::ScopeContextMenu(_controlsType, this);
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
