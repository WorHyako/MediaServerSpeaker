#include "Dialogs/RenamingDialog.hpp"

#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

using namespace Mss::Gui::Dialogs;

RenamingDialog::RenamingDialog(QWidget *parent,
                               const std::string &lastName)
        : QDialog(parent) {
    auto grid = new QGridLayout(this);
    grid->setAlignment(Qt::AlignAbsolute);

    auto lastNameTextEdit = new QTextEdit(lastName.c_str());
    lastNameTextEdit->setEnabled(false);
    grid->addWidget(lastNameTextEdit, 0, 0);

    auto newNameTextEdit = new QTextEdit;
    newNameTextEdit->setPlaceholderText("New name");
    grid->addWidget(newNameTextEdit, 1, 0);

    auto button = new QPushButton("Ok");
    grid->addWidget(button, 2, 0);

    connect(button, &QPushButton::pressed, [this, newNameTextEdit]() {
        emit renameAccepted(newNameTextEdit->toPlainText().toStdString());
        this->close();
        this->deleteLater();
    });
}
