#include "Actions/DeleteAction.hpp"

#include <QWidget>

using namespace MSS::Gui::Actions;

DeleteAction::DeleteAction(QObject *parent, QWidget *caller)
        : QAction(parent),
          IAction(caller) {
    QAction::setText("Delete");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(execute()));
}

void DeleteAction::execute() const noexcept {
    if (IAction::_caller) {
        IAction::_caller->deleteLater();
    }
}
