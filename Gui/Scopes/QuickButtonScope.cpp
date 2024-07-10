#include "precompile_header.hpp"

#include "Scopes/QuickButtonScope.hpp"

#include "Controls/ManagementButton.hpp"
#include "Config/ControlsConfig.hpp"
#include "ContextMenu/ScopeContextMenu.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

using namespace Mss::Gui::Scopes;

namespace {

    constexpr std::uint8_t rowMax = 5;

    constexpr std::uint8_t columnMax = 6;

    /**
     * @brief
     *
     * @param idx
     *
     * @return
     *
     * @author WorHyako
     */
    QPoint calculateButtonPosition(std::size_t idx) {
        std::uint8_t row = 0, column = 0;

        row = idx / (columnMax - 1);
        column = idx % rowMax;

        return { row, column };
    }
}

QuickButtonScope::QuickButtonScope(QWidget *parent) noexcept
        : QWidget(parent),
          _buttonsCount(0) {
    QWidget::move(1, 1);
    QWidget::resize(300, 200);

    auto layout = new QGridLayout(this);
    QWidget::setLayout(layout);
    layout->setSpacing(2);

    for (std::uint8_t i = 0; i < ::rowMax * ::columnMax; i++) {
        auto [row, column] = ::calculateButtonPosition(i);
        layout->addWidget(new QWidget, row, column);
    }
}

void QuickButtonScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, QWidget::width(), QWidget::height(), 5, 5);

    QWidget::paintEvent(e);
}

void QuickButtonScope::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::MouseButton::RightButton) {
        auto menu = new ContextMenu::ScopeContextMenu(ControlType::QuickButton, this);
        menu->popup(QWidget::mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}

void QuickButtonScope::addControl(ControlType controlType) noexcept {
    auto control = Config::ControlCreator<Controls::Button>::create();
    addControl(control.release());
}

void QuickButtonScope::addControl(QWidget *control) noexcept {
    if (_buttonsCount >= (::rowMax * ::columnMax - 1)) {
        control->deleteLater();
        return;
    }
    auto layout = QWidget::layout();
    if (!layout) {
        return;
    }
    auto nextCell = layout->itemAt(_buttonsCount)->widget();

    nextCell = layout->replaceWidget(nextCell, control)->widget();
    nextCell->deleteLater();

    control->show();
    _buttonsCount++;
}

void QuickButtonScope::removeControl(QWidget *control) noexcept {
//    control->hide();
//    control->setParent(nullptr);
    control->deleteLater();
}

void QuickButtonScope::loadControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    const auto &tabName = parentTab->accessibleName().toStdString();
    auto controls = Config::load(tabName, Config::ScopeType::QuickButtons);
    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void QuickButtonScope::saveControls() noexcept {

}
