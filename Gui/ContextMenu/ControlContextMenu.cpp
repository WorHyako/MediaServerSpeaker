#include "precompile_header.hpp"

#include "ControlContextMenu.hpp"

#include "Dialogs/ControlProperty.hpp"

using namespace Mss::Gui::ContextMenu;

ControlContextMenu::ControlContextMenu(QWidget *parent) noexcept
        : QMenu(parent) {
    auto propertyDialog = Config::ControlCreator<Dialogs::ControlProperty>::create(parent);

    auto propertyAction = new QAction("Property");
    connect(propertyAction, SIGNAL(triggered(bool)), propertyDialog.get(), SLOT(show()));

    auto deleteAction = new QAction("Delete");
    connect(deleteAction, SIGNAL(triggered(bool)), parent, SLOT(deleteLater()));

    QMenu::addActions({ propertyAction, deleteAction });

    std::ignore = propertyDialog.release();
}
