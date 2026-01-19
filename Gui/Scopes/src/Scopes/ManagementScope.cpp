#include "Scopes/ManagementScope.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/ManagementTextableButton.hpp"

import mss.gui.scopes;

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

ManagementScope::ManagementScope(QWidget *parent) noexcept
    : IScope{ parent } {
    IScope::controls_type_ = ControlType::ManagementButton | ControlType::ManagementTextableButton | ControlType::Table;
}

void ManagementScope::add_control(QWidget *control) noexcept {
    auto mv_control{ dynamic_cast<IMovableControl *>(control) };
    if (!mv_control) {
        return;
    }

    mv_control->edit_mode(edit_mode_);
    mv_control->setParent(this);
    mv_control->show();
}

void ManagementScope::remove_control(QWidget *control) noexcept {
    if (!control) {
        return;
    }
    control->setParent(nullptr);
    control->deleteLater();
}

void ManagementScope::remove_all_controls() noexcept {
    auto children{ QWidget::children() };
    std::ranges::for_each(children, [this](QObject *each) {
        const auto control{ dynamic_cast<IMovableControl *>(each) };
        if (!control) {
            return;
        }
        remove_control(control);
    });
}

void ManagementScope::load_controls() noexcept {
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
    const std::string tab_name{parent_tab->accessibleName().toUtf8().constData()};

    Config<ManagementScope> config{tab_name};
    if (!config.load_config()) {
        return;
    }

    auto mb_controls{ config.load_from_config<ManagementButton>() };
    auto mtb_controls{ config.load_from_config<ManagementTextableButton>() };

    WorQWidgetPtrVec controls;

    controls.reserve(std::size(mb_controls) + std::size(mtb_controls));
    controls.insert(
        std::cend(controls),
        std::make_move_iterator(std::begin(mb_controls)),
        std::make_move_iterator(std::end(mb_controls))
    );
    controls.insert(
        std::cend(controls),
        std::make_move_iterator(std::begin(mtb_controls)),
        std::make_move_iterator(std::end(mtb_controls))
    );

    /**
     * TODO: finish
     */
    std::ranges::for_each(controls, [this](auto &each) {
        add_control(each.release());
    });
}

void ManagementScope::save_controls() noexcept {
    const auto &parent_tab{ dynamic_cast<QWidget *>(QWidget::parent()) };
    if (!parent_tab) {
        return;
    }
    const std::string tabName{parent_tab->accessibleName().toUtf8().constData()};
    Config<ManagementScope> config{tabName};
    config.add_to_config<ManagementButton>(this);
    config.add_to_config<ManagementTextableButton>(this);
    std::ignore = config.save_config();
}

#pragma region Callbacks

void ManagementScope::edit_mode_change(bool toggled) {
    auto children{ QWidget::children() };

    IScope::edit_mode_change(toggled, children);
}

#pragma endregion Callbacks
