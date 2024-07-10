#include "Actions/RenameAction.hpp"

#include "Dialogs/RenamingDialog.hpp"

#include <QAbstractButton>

using namespace Mss::Gui::Actions;
using namespace Mss::Gui;

RenameAction::RenameAction(QObject *parent, QWidget *caller)
        : QAction(parent),
          IAction(caller) {
    QAction::setText("Rename");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(execute()));
}

void RenameAction::execute() const noexcept {
    auto button = dynamic_cast<QAbstractButton*>(IAction::_caller);
    if (!button) {
        return;
    }
    auto renamingDialog = new Dialogs::RenamingDialog(nullptr, button->text().toStdString());
    renamingDialog->resize(200, 200);
    connect(renamingDialog, &Dialogs::RenamingDialog::renameAccepted,
            [button](const std::string &newName) {
                if (button) {
                    button->setText({ newName.c_str() });
                }
            });

    renamingDialog->show();
}
