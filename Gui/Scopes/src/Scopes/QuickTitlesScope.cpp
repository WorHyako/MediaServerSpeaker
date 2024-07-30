#include "QuickTitlesScope.hpp"

#include "Controls/QuickTitle.hpp"

#include "Config.hpp"
#include "ScopeContextMenu.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

QuickTitlesScope::QuickTitlesScope(QWidget *parent) noexcept
        : QWidget(parent) {
    auto layout = new QVBoxLayout;

    layout->setAlignment(Qt::AlignmentFlag::AlignTop);
    layout->setSpacing(5);

    QWidget::setLayout(layout);
}

void QuickTitlesScope::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::MouseButton::RightButton) {
        auto menu = new Menus::ScopeContextMenu(ControlType::QuickTitle, this);
        menu->popup(QWidget::mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}

void QuickTitlesScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);

    QWidget::paintEvent(e);
}

void QuickTitlesScope::addControl(QWidget *control) noexcept {
    control->setFixedHeight(50);

    QWidget::layout()->addWidget(control);
}

void QuickTitlesScope::removeControl(QWidget *control) noexcept {
    QWidget::layout()->removeWidget(control);
    control->deleteLater();
}

void QuickTitlesScope::removeAllControls() noexcept {
    auto children = QWidget::children();
    std::for_each(std::begin(children), std::end(children), [this](QObject *each) {
        auto control = dynamic_cast<BaseControl *>(each);
        if (!control) {
            return;
        }
        removeControl(control);
    });
}

void QuickTitlesScope::loadControls() noexcept {
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
    Config <QuickTitlesScope> config(tabName);
    if (!config.loadConfig()) {
        return;
    }

    auto controls = config.loadFromConfig<QuickTitle>();

    /**
     * TODO: finish
     */
    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void QuickTitlesScope::saveControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    const auto &tabName = parentTab->accessibleName().toStdString();
    Config <QuickTitlesScope> config(tabName);
    config.addToConfig<QuickTitle>(this);
    if (!config.saveConfig()) {
        std::printf("Fail in saving process.\n");
    }
}
