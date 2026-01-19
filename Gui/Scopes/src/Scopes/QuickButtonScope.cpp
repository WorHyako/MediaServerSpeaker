#include "QuickButtonScope.hpp"

#include "Controls/QuickButton.hpp"

#include <QGridLayout>

import mss.gui.scopes;

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

namespace {
/**
 * @brief	Grid's row count.
 */
constexpr std::uint8_t row_max = 5;

/**
 * @brief	Grid's colum count.
 */
constexpr std::uint8_t column_max = 6;

/**
 * @brief	Calculate grid position of control by current index.
 *
 * @param	idx	Control index.
 *
 * @return	Grid coordinates.
 *
 * @author	WorHyako
 */
[[nodiscard]]
QPoint calculate_button_position(std::size_t idx) {
    auto row{ static_cast<int>(idx) / (::column_max - 1) };
    auto column{ static_cast<int>(idx) % ::row_max };

    return { row, column };
}
}

QuickButtonScope::QuickButtonScope(QWidget *parent) noexcept
    : IScope{ parent },
      buttons_count_{ 0 } {
    controls_type_ = ControlType::QuickButton;
    QWidget::move(1, 1);

    const auto layout{ new QGridLayout };
    QWidget::setLayout(layout);
    layout->setSpacing(2);

    for (auto i{ 0 }; i < ::row_max * ::column_max; i++) {
        const auto [row, column]{ ::calculate_button_position(i) };
        layout->addWidget(new QWidget, row, column);
        //        std::printf("Kids count - %lli\n", layout->children().size());
    }
}

void QuickButtonScope::add_control(QWidget *control) noexcept {
    if (buttons_count_ >= (::row_max * ::column_max - 1)) {
        control->deleteLater();
        return;
    }
    auto layout{ QWidget::layout() };
    auto next_cell{ layout->itemAt(buttons_count_)->widget() };

    next_cell = layout->replaceWidget(next_cell, control, Qt::FindChildOption::FindDirectChildrenOnly)->widget();
    next_cell->deleteLater();

    std::ignore = connect(control, &QWidget::destroyed, [this](QObject *t) {
        remove_control(dynamic_cast<QWidget *>(t));
    });

    buttons_count_++;
}

void QuickButtonScope::remove_control(QWidget *control) noexcept {
    const auto layout{ QWidget::layout() };
    const auto idx{ layout->indexOf(control) };
    const auto item{ layout->itemAt(idx) };
    item->widget()->deleteLater();
    control->deleteLater();

    layout->update();

    buttons_count_--;
}

void QuickButtonScope::remove_all_controls() noexcept {
    auto all_controls{ QWidget::layout()->children() };
    std::ranges::for_each(all_controls, [this](QObject *each) {
        const auto control{ dynamic_cast<QWidget *>(each) };
        if (!control) {
            return;
        }
        remove_control(control);
    });
}

void QuickButtonScope::load_controls() noexcept {
    const auto &parent_tab{ dynamic_cast<QWidget *>(QWidget::parent()) };
    if (!parent_tab) {
        return;
    }
    /**
     * TODO: first thread
     */
    remove_all_controls();

    /**
     * TODO: second thread
     */
    const std::string tab_name(parent_tab->accessibleName().toUtf8().constData());
    Config<QuickButtonScope> config(tab_name);
    if (!config.load_config()) {
        return;
    }
    auto controls{ config.load_from_config<QuickButton>() };

    /**
     * TODO: finish
     */
    std::ranges::for_each(controls, [this](auto &each) {
        add_control(each.release());
    });
}

void QuickButtonScope::save_controls() noexcept {
    const auto &parentTab{ dynamic_cast<QWidget *>(QWidget::parent()) };
    if (!parentTab) {
        return;
    }
    const std::string tab_name{ parentTab->accessibleName().toUtf8().constData() };
    Config<QuickButtonScope> config(tab_name);
    config.add_to_config<QuickButton>(this);
    std::ignore = config.save_config();
}

void QuickButtonScope::move_all_left_since(std::uint8_t idx) noexcept {
    const auto layout{ QWidget::layout() };
    for (auto i{ idx }; i < buttons_count_ - 1; ++i) {
        auto current{ layout->takeAt(i) };
        auto next{ layout->takeAt(i + 1) };
        auto temp{ current };
    }
}

#pragma region Callbacks

void QuickButtonScope::edit_mode_change(bool toggled) {
}

#pragma endregion Callbacks
