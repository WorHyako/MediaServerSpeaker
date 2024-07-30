#include "ControlProperty.hpp"

#include "MovableBaseControl.hpp"

#include "Style/WorStyle.hpp"

#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QStyle>

using namespace Mss::Gui::Controls::Dialogs;
using namespace Mss::Backend::Command;

ControlProperty::ControlProperty(QWidget *parent) noexcept
        : QDialog(parent),
          _commandLayout(nullptr),
          _control(nullptr),
          _controlName() {
    _control = dynamic_cast<Controls::MovableBaseControl *>(parent);
    if (!_control) {
        QDialog::deleteLater();
        return;
    }
    QDialog::setWindowTitle(parent->accessibleName());

    QDialog::setStyleSheet(Style::getWorStyle().c_str());
    auto vLayout = new QVBoxLayout(this);
    QDialog::setLayout(vLayout);
    vLayout->setSpacing(5);
    _testCommand = std::make_unique<BaseCommand>();
    _testCommand->markTag(_control->getCommand()->getTag());

    {
        /**
         * Control name
         */
        auto hLayout = new QHBoxLayout;

        auto controlNameText = new QTextEdit;
        controlNameText->setText(_control->getText().c_str());
        hLayout->addWidget(controlNameText);

        connect(controlNameText, &QTextEdit::textChanged, [this, controlNameText]() {
            _controlName = controlNameText->toPlainText().toStdString();
        });

        vLayout->addLayout(hLayout);
    }

    auto commandTag = new QTextEdit(_testCommand->getTag().c_str());
    connect(commandTag, &QTextEdit::textChanged, [commandTag, this]() {
        _testCommand->markTag(commandTag->toPlainText().toStdString());
        emit fullCommandChanged(_testCommand->str().c_str());
    });
    vLayout->addWidget(commandTag);

    {
        /**
         * Command items layout command
         */
        _commandLayout = new QVBoxLayout(vLayout->widget());

        auto controlItems = _control->getCommand()->getItems();
        std::for_each(std::begin(controlItems), std::end(controlItems), [this](const CommandItem &each) {
            addCommandItemHLayout(each);
        });
    }
    vLayout->addLayout(_commandLayout);

    /**
     * Buttons layout for command items
     */
    auto buttonsLayout = new QHBoxLayout;

    auto addCommandItemButton = new QPushButton("Add");
    connect(addCommandItemButton, &QPushButton::pressed, [this]() {
        addCommandItemHLayout();
    });
    buttonsLayout->addWidget(addCommandItemButton);
    vLayout->addLayout(buttonsLayout);

    /**
     * Full command widget
     */
    auto fullCommand = new QTextEdit(_testCommand->str().c_str());
    fullCommand->setFixedHeight(50);
    connect(this, SIGNAL(fullCommandChanged(QString)), fullCommand, SLOT(setText(QString)));
    fullCommand->setEnabled(false);
    vLayout->addWidget(fullCommand);

    /**
     * Common buttons
     */
    auto hCommonLayout = new QHBoxLayout;
    auto okButton = new QPushButton("Ok");
    connect(okButton, &QPushButton::pressed, [this]() {
        applyChanged();
    });
    hCommonLayout->addWidget(okButton);

    auto cancelButton = new QPushButton("Cancel");
    connect(cancelButton, &QPushButton::pressed, [this]() {
        QDialog::close();
    });
    hCommonLayout->addWidget(cancelButton);

    vLayout->addLayout(hCommonLayout);
}

void ControlProperty::addCommandItemHLayout(const CommandItem &item) noexcept {
    auto hLayout = new QHBoxLayout();
    {
        auto idx = _testCommand->indexOf(item.key());
        if (idx != -1) {
            return;
        }
    }
    _testCommand->addItem(item);

    auto keyText = new QTextEdit(item.key().c_str());
    connect(keyText, &QTextEdit::textChanged, [keyText, hLayout, this]() {
        auto idx = _commandLayout->indexOf(hLayout);
        auto value = _testCommand->getItems()[idx].value();
        emit refreshCommand(idx, { keyText->toPlainText().toStdString(), value });
    });

    keyText->setStyleSheet(Style::getTextEditStyle().data());
    hLayout->addWidget(keyText);

    auto valueText = new QTextEdit(item.value().c_str());
    connect(valueText, &QTextEdit::textChanged, [valueText, hLayout, this]() {
        auto idx = _commandLayout->indexOf(hLayout);
        auto key = _testCommand->getItems()[idx].key();
        emit refreshCommand(idx, { key, valueText->toPlainText().toStdString() });
    });
    hLayout->addWidget(valueText);

    auto removeButton = new QPushButton("Remove");
    removeButton->setFixedHeight(50);

    connect(removeButton, &QPushButton::pressed, [this, hLayout]() {
        removeCommandItemHLayout(hLayout);
    });
    hLayout->addWidget(removeButton);

    _commandLayout->addLayout(hLayout);
}

void ControlProperty::removeCommandItemHLayout(QHBoxLayout *hLayout) noexcept {
    auto idx = _commandLayout->indexOf(hLayout);
    _testCommand->removeItem(idx);

    _commandLayout->removeItem(hLayout);

    auto layoutItem = hLayout->takeAt(0)->widget();
    if (layoutItem) {
        layoutItem->deleteLater();
    }

    _commandLayout->update();

    emit fullCommandChanged(_testCommand->str().c_str());
}

void ControlProperty::refreshCommand(std::uint16_t idx, const CommandItem &item) {
    _testCommand->changeItem(idx, item);

    emit fullCommandChanged(_testCommand->str().c_str());

//    std::printf("***** Printing command items from ControlProperty: ****\n");
//    auto items = _testCommand->getItems();
//    std::for_each(std::begin(items), std::end(items), [](const CommandItem &each) {
//        std::printf("key: %s,\t value: %s\n", each.key().c_str(), each.value().c_str());
//    });
}

void ControlProperty::applyChanged() noexcept {
    _control->setCommand(_testCommand.release());
    emit _control->commandChanged();

    _control->setText(_controlName);

    QDialog::close();
}
