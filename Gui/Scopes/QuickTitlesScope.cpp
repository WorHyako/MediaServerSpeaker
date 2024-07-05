#include "QuickTitlesScope.hpp"

#include <QPainter>

using namespace Mss::Gui::Scopes;

QuickTitlesScope::QuickTitlesScope(QWidget *parent)
        : QStackedWidget(parent) {
}

void QuickTitlesScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);

    QStackedWidget::paintEvent(e);
}
