#include "Scopes/ManagementScope.hpp"

#include "ContextMenu/ScopeContextMenu.hpp"

#include "Controls/MovableBaseControl.hpp"
#include "Controls/Config.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

#include <memory>

using namespace Mss::Gui::Scopes;

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
                                                      ControlType::ManagementTextableButton,
                                                      this);
        menu->popup(QWidget::mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}

void ManagementScope::addControl(QWidget *control) noexcept {
    control->setParent(this);
    control->show();
}

void ManagementScope::removeControl(QWidget *control) noexcept {
    control->setParent(nullptr);
    control->deleteLater();
}

void ManagementScope::removeAllControls() noexcept {
    auto children = QWidget::children();
    std::for_each(std::begin(children), std::end(children), [this](QObject *each) {
        auto control = dynamic_cast<Controls::MovableBaseControl *>(each);
        if (!control) {
            return;
        }
        removeControl(control);
    });
}

void ManagementScope::loadControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    /**
     * TODO: first thread
     */
    removeAllControls();

    /**
     * TODO: second thread
     */
    const auto &tabName = parentTab->accessibleName().toStdString();
    auto controls = Controls::Config::load<ManagementScope>(tabName);

    /**
     * TODO: finish
     */
    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void ManagementScope::saveControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    const auto &tabName = parentTab->accessibleName().toStdString();
    auto saveRes = Controls::Config::save<ManagementScope>(tabName, this);
}
