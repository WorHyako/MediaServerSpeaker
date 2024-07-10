#include "Dialogs/ControlProperty.hpp"

#include "Controls/IControl.hpp"

#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

using namespace Mss::Gui::Dialogs;

ControlProperty::ControlProperty(QWidget *parent) noexcept
        : QDialog(parent) {
    auto control = dynamic_cast<Controls::IControl *>(parent);
    if (!control) {
        return;
    }

    auto vLayout = new QVBoxLayout(this);
    QDialog::setLayout(vLayout);
    vLayout->setSpacing(5);

    auto controlName = new QTextEdit("Control Name");
//    controlName->setEnabled(false);
    vLayout->addWidget(controlName);
    {
        /**
         * Control name
         */
        auto hLayout = new QHBoxLayout;
        auto text = new QTextEdit;
        auto button = new QPushButton("Apply");
        connect(button, &QPushButton::pressed, [text, control]() {
            control->setText(text->toPlainText().toStdString());
        });

        hLayout->addWidget(text);
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
    {
        /**
         * Control name
         */
        auto hLayout = new QHBoxLayout;
        auto text = new QTextEdit;
        auto button = new QPushButton;
        hLayout->addWidget(text);
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
}
