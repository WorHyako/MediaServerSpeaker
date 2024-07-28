#include "Scopes/QuickButtonScope.hpp"

#include "Controls/Config.hpp"
#include "Controls/ControlCreator.hpp"
#include "Controls/QuickButton.hpp"

#include "ContextMenu/ScopeContextMenu.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QSpacerItem>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

namespace {

    /**
     * @brief
     */
    constexpr std::uint8_t rowMax = 5;

    /**
     * @brief
     */
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
        std::uint8_t row = idx / (::columnMax - 1);
        std::uint8_t column = idx % ::rowMax;

        return { row, column };
    }
}

QuickButtonScope::QuickButtonScope(QWidget *parent) noexcept
        : QWidget(parent),
          _buttonsCount(0) {
    QWidget::move(1, 1);

    auto layout = new QGridLayout;
    QWidget::setLayout(layout);
    layout->setSpacing(2);

    for (std::uint8_t i = 0; i < ::rowMax * ::columnMax; i++) {
        auto [row, column] = ::calculateButtonPosition(i);
        layout->addWidget(new QWidget, row, column);
        std::printf("Kids count - %lli\n", layout->children().size());
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

void QuickButtonScope::addControl(QWidget *control) noexcept {
    if (_buttonsCount >= (::rowMax * ::columnMax - 1)) {
        control->deleteLater();
        return;
    }
    auto layout = QWidget::layout();
    auto nextCell = layout->itemAt(_buttonsCount)->widget();

    nextCell = layout->replaceWidget(nextCell, control, Qt::FindChildOption::FindDirectChildrenOnly)->widget();
    nextCell->deleteLater();

    connect(control, &QWidget::destroyed, [this](QObject *t) {
        removeControl(dynamic_cast<QWidget *>(t));
    });

    _buttonsCount++;
    std::printf("Kids count - %lli\n", layout->children().size());
}

void QuickButtonScope::removeControl(QWidget *control) noexcept {
    auto layout = QWidget::layout();
    std::uint8_t idx = layout->indexOf(control);
//    layout->removeWidget(control);
    auto item = layout->itemAt(idx);
    item->widget()->deleteLater();
    control->deleteLater();

//    layout->removeWidget(control);
//    delete control;
//    control->deleteLater();
//    layout->removeItem();
//    layout->replaceWidget(control, new QWidget, Qt::FindChildOption::FindDirectChildrenOnly);
//    control->deleteLater();

//    moveAllLeftSince(idx);
    layout->update();

    _buttonsCount--;
}

void QuickButtonScope::removeAllControls() noexcept {
    auto allControls = QWidget::layout()->children();
    std::for_each(std::begin(allControls), std::end(allControls), [this](QObject *each) {
        auto control = dynamic_cast<QWidget *>(each);
        if (!control) {
            return;
        }
        removeControl(control);
    });
}

void QuickButtonScope::loadControls() noexcept {
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
    Config <QuickButtonScope> config(tabName);
    if (!config.loadConfig()) {
        return;
    }
    auto controls = config.loadFromConfig<QuickButton>();

    /**
     * TODO: finish
     */
    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void QuickButtonScope::saveControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    const auto &tabName = parentTab->accessibleName().toStdString();
    Config <QuickButtonScope> config(tabName);
    config.addToConfig<QuickButton>(this);
    if (!config.saveConfig()) {
        std::printf("Error in saving process.\n");
    }
}

void QuickButtonScope::moveAllLeftSince(std::uint8_t idx) noexcept {
    auto layout = QWidget::layout();
    for (std::uint8_t i = idx; i < _buttonsCount - 1; ++i) {
        auto current = layout->takeAt(i);
        auto next = layout->takeAt(i + 1);
        auto temp = current;
    }
}
