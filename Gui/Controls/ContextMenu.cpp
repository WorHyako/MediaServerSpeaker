#include "Controls/ContextMenu.hpp"
#include "Actions/RenameAction.hpp"

#include <QHideEvent>

using namespace MSS::Gui::Controls;
using namespace MSS::Gui;

ContextMenu::ContextMenu(QWidget *parent)
        : QMenu(parent) {
    QMenu::resize(100, 100);
    QMenu::hide();
}

void ContextMenu::setActions(const std::vector<QAction *> &actions) noexcept {
    for (auto each : actions) {
        _actions.emplace_back(std::unique_ptr<QAction>(each));

        auto *lastAction = _actions.back().get();
        QMenu::addAction(lastAction);
    }
}
