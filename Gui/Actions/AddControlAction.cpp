#include "Actions/AddControlAction.hpp"

#include "Controls/ManagementButton.hpp"

#include <QWidget>

using namespace MSS::Gui::Actions;

AddControlAction::AddControlAction(QObject *parent, QWidget *caller)
        : QAction(parent),
          IAction(caller) {
    QAction::setText("Add new");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(execute()));
}

void AddControlAction::execute() const noexcept {
    auto button = new Controls::ManagementButton(_caller);
    button->setContextMenuEnable(true);
}
