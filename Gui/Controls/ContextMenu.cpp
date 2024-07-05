#include "Controls/ContextMenu.hpp"

#include "Actions/RenameAction.hpp"

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

ContextMenu::ContextMenu(QWidget *parent)
        : QMenu(parent) {
    QMenu::resize(100, 100);
}

void ContextMenu::setActions(const std::vector<QAction *> &actions) noexcept {
    for (auto each : actions) {
        _actions.emplace_back(std::unique_ptr<QAction>(each));

        auto *lastAction = _actions.back().get();
        QMenu::addAction(lastAction);
    }
}
