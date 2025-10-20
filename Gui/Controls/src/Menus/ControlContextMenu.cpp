#include "Menus/ControlContextMenu.hpp"

#include "ControlProperty.hpp"

#include "Creators/ControlCreator.hpp"

using namespace Mss::Gui::Controls::Menus;

ControlContextMenu::ControlContextMenu(QWidget *parent) noexcept
    : QMenu{ parent } {
    std::ignore = connect(this, SIGNAL(aboutToShow()), this, SLOT(configure()));
    std::ignore = connect(this, SIGNAL(aboutToHide()), this, SLOT(reset()));
}

void ControlContextMenu::configure() {
    const auto parent{ dynamic_cast<QWidget *>(QMenu::parent()) };
    if (!parent) {
        return;
    }
    auto property_dialog{ Controls::ControlCreator<Dialogs::ControlProperty>::create(parent) };
    std::ignore = connect(property_dialog.get(), SIGNAL(finished(int)), property_dialog.get(), SLOT(deleteLater()));

    auto property_action{ new QAction("Property") };
    std::ignore = connect(property_action, SIGNAL(triggered(bool)), property_dialog.get(), SLOT(show()));

    auto delete_action{ new QAction("Delete") };
    std::ignore = connect(delete_action, SIGNAL(triggered(bool)), parent, SLOT(deleteLater()));

    QMenu::addActions({ property_action, delete_action });

    std::ignore = property_dialog.release();
}

void ControlContextMenu::reset() {
    QMenu::clear();
}
