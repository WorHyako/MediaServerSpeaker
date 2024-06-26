#include "Scopes/ManagementScope.hpp"

#include "Controls/ContextMenu.hpp"
#include "Actions/AddControlAction.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

using namespace MSS::Gui::Scopes;

ManagementScope::ManagementScope(QWidget *parent)
        : QWidget(parent),
          _layout(nullptr) {
}

void ManagementScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);

    QWidget::paintEvent(e);
}

void ManagementScope::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::MouseButton::RightButton) {
        auto menu = new Controls::ContextMenu;
        auto addNewAction = new Actions::AddControlAction(menu, this);
        menu->addAction(addNewAction);
        menu->popup(mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}
