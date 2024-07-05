#include "Scopes/QuickButtonScope.hpp"

#include "Controls/ManagementButton.hpp"

#include <QGridLayout>
#include <QPainter>

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

QuickButtonScope::QuickButtonScope(QWidget *parent)
        : QWidget(parent),
          _layout(nullptr),
          _buttonsCount(0) {
    QWidget::move(1, 1);
    QWidget::resize(300, 200);

    _layout = new QGridLayout(this);
    _layout->setSpacing(2);

    for (std::uint8_t i = 0; i < ::rowMax * ::columnMax; i++) {
        auto [row, column] = ::calculateButtonPosition(i);
        _layout->addWidget(new QWidget, row, column);
    }

    auto addButton = new Controls::ManagementButton(this);
    addButton->setContextMenuEnable(false);
    addButton->setText("+");
    connect(addButton, SIGNAL(pressed()), this, SLOT(addButton()));
    addButton->show();

    auto trash = _layout->itemAtPosition(0, 0)->widget();
    trash = _layout->replaceWidget(trash, addButton)->widget();
    trash->deleteLater();
}

void QuickButtonScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);

    QWidget::paintEvent(e);
}

void QuickButtonScope::addButton() noexcept {
    if (_buttonsCount >= (::rowMax * ::columnMax - 1)) {
        return;
    }
    auto newButton = new Controls::ManagementButton(this);
    newButton->setText(QString::number(_buttonsCount));

    auto addButton = _layout->itemAt(_buttonsCount)->widget();

    addButton = _layout->replaceWidget(addButton, newButton)->widget();

    auto trash = _layout->itemAt(_buttonsCount + 1)->widget();
    trash = _layout->replaceWidget(trash, addButton)->widget();
    trash->deleteLater();

    newButton->show();
    _buttonsCount++;
}
