#include "QuickTitlesScope.hpp"

#include "Config.hpp"
#include "Controls/QuickTitle.hpp"

#include <QVBoxLayout>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

QuickTitlesScope::QuickTitlesScope(QWidget *parent) noexcept
    : IScope{ parent } {
    controls_type_ = ControlType::QuickTitle;
    auto layout{ new QVBoxLayout };
    QWidget::setLayout(layout);

    layout->setAlignment(Qt::AlignmentFlag::AlignTop);
    layout->setSpacing(5);
}

void QuickTitlesScope::add_control(QWidget *control) noexcept {
    control->setFixedHeight(50);

    QWidget::layout()->addWidget(control);
}

void QuickTitlesScope::remove_control(QWidget *control) noexcept {
    QWidget::layout()->removeWidget(control);
    control->deleteLater();
}

void QuickTitlesScope::remove_all_controls() noexcept {
    auto children{ QWidget::children() };
    std::ranges::for_each(children, [this](QObject *each) {
        const auto control{ dynamic_cast<IControl *>(each) };
        if (!control) {
            return;
        }
        remove_control(control);
    });
}

void QuickTitlesScope::load_controls() noexcept {
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
    const std::string tab_name{ parent_tab->accessibleName().toUtf8().constData() };
    Config<QuickTitlesScope> config{ tab_name };
    if (!config.load_config()) {
        return;
    }

    auto controls{ config.load_from_config<QuickTitle>() };

    /**
     * TODO: finish
     */
    std::ranges::for_each(controls, [this](auto &each) {
        add_control(each.release());
    });
}

void QuickTitlesScope::save_controls() noexcept {
    const auto &parent_tab{ dynamic_cast<QWidget *>(QWidget::parent()) };
    if (!parent_tab) {
        return;
    }
    const std::string tab_name{ parent_tab->accessibleName().toUtf8().constData() };
    Config<QuickTitlesScope> config{ tab_name };
    config.add_to_config<QuickTitle>(this);
    std::ignore = config.save_config();
}

#pragma region Callbacks

void QuickTitlesScope::edit_mode_change(bool toggled) {
}

#pragma endregion Callbacks
