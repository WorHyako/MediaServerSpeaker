#include "Scopes/ManagementScope.hpp"

#include "ContextMenu/ScopeContextMenu.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/Config.hpp"
#include "Controls/ControlCreator.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

#include <memory>

using namespace Mss::Gui::Scopes;

//extern template Mss::Gui::Controls::WorQWidgetPtrVec
//        Mss::Gui::Controls::Config<ManagementScope>::load(const std::string &);

ManagementScope::ManagementScope(QWidget *parent) noexcept
        : QWidget(parent) {
}

void ManagementScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, QWidget::width(), QWidget::height(), 5, 5);

    QWidget::paintEvent(e);
}

void ManagementScope::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::MouseButton::RightButton) {
        auto menu = new ContextMenu::ScopeContextMenu(ControlType::ManagementButton |
                                                      ControlType::Button,
                                                      this);
        menu->popup(QWidget::mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}

void ManagementScope::addControl(ControlType controlType) noexcept {
    std::unique_ptr<QWidget> control;
    switch (controlType) {
        case ControlType::Button:
            control = Controls::ControlCreator<Controls::Button>::create(this);
            break;
        case ControlType::ManagementButton:
            control = Controls::ControlCreator<Controls::ManagementButton>::create(this);
            break;
        default:
            return;
    }
    control->show();
    std::ignore = control.release();
}

void ManagementScope::addControl(QWidget *control) noexcept {
    control->setParent(this);
    control->show();
}

void ManagementScope::removeControl(QWidget *control) noexcept {
    control->hide();
    control->setParent(nullptr);
    control->deleteLater();
}

void ManagementScope::loadControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    const auto &tabName = parentTab->accessibleName().toStdString();
    auto controls = Controls::Config<ManagementScope>::load(tabName);

    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void ManagementScope::saveControls() noexcept {

}
