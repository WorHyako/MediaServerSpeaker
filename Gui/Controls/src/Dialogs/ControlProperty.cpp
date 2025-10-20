#include "ControlProperty.hpp"

#include "Interfaces/IMovableControl.hpp"

#include "Style/WorStyle.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Mss::Gui::Controls::Dialogs;
using namespace Mss::Backend::Command;

ControlProperty::ControlProperty(QWidget *parent) noexcept
    : QDialog{ parent },
      control_{ dynamic_cast<Controls::IMovableControl *>(parent) },
      command_layout_{ nullptr },
      midi_button_id_{ 0 } {
    if (!control_) {
        QDialog::deleteLater();
        return;
    }

    QDialog::setWindowTitle(parent->accessibleName());
    QDialog::setStyleSheet(Style::get_wor_style().c_str());

    auto hlayout{ new QHBoxLayout };
    QDialog::setLayout(hlayout);
    auto label_layout{ new QVBoxLayout };
    auto text_layout{ new QVBoxLayout };

    hlayout->addLayout(label_layout);
    hlayout->addLayout(text_layout);

    test_command_ = std::make_unique<BaseCommand>();
    test_command_->set(control_->command()->str());
    control_name_ = control_->get_text();
    midi_button_id_ = control_->get_midi_key_idx();

    {
        /**
         * Control name
         */
        auto text{ new QLineEdit(control_name_.c_str()) };
        text_layout->addWidget(text);

        auto label{ new QLabel("Control Name") };
        label_layout->addWidget(label);

        std::ignore = connect(text, &QLineEdit::textChanged, [this, text]() {
            control_name_ = text->text().toUtf8().constData();
        });
    }
    {
        /**
         * MidiIdx
         */
        auto text{ new QLineEdit(QString::number(control_->get_midi_key_idx())) };
        text_layout->addWidget(text);

        auto label{ new QLabel("Midi button ID") };
        label_layout->addWidget(label);

        std::ignore = connect(text, &QLineEdit::textChanged, [&midiButtonId = midi_button_id_, text]() {
            midiButtonId = text->text().toInt();
        });
    }
    {
        /**
         * Command tag
         */
        auto text{ new QLineEdit(test_command_->get_tag().c_str()) };
        text_layout->addWidget(text);

        auto label{ new QLabel("Command tag") };
        label_layout->addWidget(label);

        std::ignore = connect(text, &QLineEdit::textChanged, [text, this]() {
            test_command_->set_tag(text->text().toUtf8().constData());
            emit full_command_changed(test_command_->str().c_str());
        });
    }
    {
        /**
         * Command items layout command
         */
        command_layout_ = new QVBoxLayout;

        auto command_items{ test_command_->items() };
        std::ranges::for_each(command_items, [this](const CommandItem &each) {
            add_command_item_hlayout(each, false);
        });
        text_layout->addLayout(command_layout_);
    }
    {
        /**
         * Buttons layout for command items
         */
        auto buttons_layout{ new QHBoxLayout };

        auto add_command_item_button{ new QPushButton("Add") };
        std::ignore = connect(add_command_item_button, &QPushButton::pressed, [this]() {
            add_command_item_hlayout();
        });
        buttons_layout->addWidget(add_command_item_button);
        text_layout->addLayout(buttons_layout);
    }
    {
        /**
         * Full command widget
         */
        auto text{ new QLineEdit(test_command_->str().c_str()) };
        text->setEnabled(false);
        text_layout->addWidget(text);

        auto label{ new QLabel("Full command") };
        label_layout->addWidget(label);

        std::ignore = connect(this, &ControlProperty::full_command_changed, text, &QLineEdit::textChanged);
    }
    {
        /**
         * Session name
         */
        auto text{ new QLineEdit(control_->get_session_name().c_str()) };
        text_layout->addWidget(text);

        auto label{ new QLabel("Session name") };
        label_layout->addWidget(label);

        std::ignore = connect(text, &QLineEdit::textChanged, [this, text]() {
            session_name_ = text->text().toUtf8().constData();
        });
    }
    {
        /**
         * Common buttons
         */
        auto layout{ new QHBoxLayout };
        auto ok_button{ new QPushButton("Ok") };
        std::ignore = connect(ok_button, &QPushButton::pressed, this, &ControlProperty::apply_changed);
        layout->addWidget(ok_button);

        auto cancel_button{ new QPushButton("Cancel") };
        std::ignore = connect(cancel_button, &QPushButton::pressed, [this]() {
            QDialog::close();
        });
        layout->addWidget(cancel_button);

        text_layout->addLayout(layout);
    }

    emit full_command_changed(test_command_->str().c_str());
}

void ControlProperty::add_command_item_hlayout(const CommandItem &item, bool unique) noexcept {
    if (unique) {
        if (test_command_->indexOf(item.key()) != -1) {
            return;
        }
        test_command_->add_item(item);
    }

    auto hlayout{ new QHBoxLayout };
    auto key_text{ new QLineEdit(item.key().c_str()) };
    std::ignore = connect(key_text, &QLineEdit::textChanged, [key_text, hlayout, this]() {
        const auto idx{ command_layout_->indexOf(hlayout) };
        const auto value{ test_command_->items()[idx].value() };
        emit refresh_command(idx, { key_text->text().toUtf8().constData(), value });
    });

    key_text->setStyleSheet(Style::get_text_edit_style().data());
    hlayout->addWidget(key_text);

    auto value_text{ new QLineEdit(item.value().c_str()) };
    std::ignore = connect(value_text, &QLineEdit::textChanged, [value_text, hlayout, this]() {
        const auto idx{ command_layout_->indexOf(hlayout) };
        const auto key{ test_command_->items()[idx].key() };
        emit refresh_command(idx, { key, value_text->text().toUtf8().constData() });
    });
    hlayout->addWidget(value_text);

    auto remove_button{ new QPushButton("Remove") };
    remove_button->setFixedHeight(50);

    std::ignore = connect(remove_button, &QPushButton::pressed, [this, hlayout]() {
        remove_command_item_hlayout(hlayout);
    });
    hlayout->addWidget(remove_button);

    command_layout_->addLayout(hlayout);
}

void ControlProperty::remove_command_item_hlayout(QHBoxLayout *hlayout) noexcept {
    const auto idx{ command_layout_->indexOf(hlayout) };
    test_command_->remove_item(idx);

    command_layout_->removeItem(hlayout);

    while (hlayout->count() > 0) {
        if (auto layout_item{ hlayout->takeAt(0)->widget() }) {
            layout_item->deleteLater();
        }
    }
    command_layout_->update();

    emit full_command_changed(test_command_->str().c_str());
}

#pragma region Callbacks

void ControlProperty::apply_changed() noexcept {
    control_->command(test_command_.release());
    emit control_->command_changed();

    control_->set_text(control_name_);
    control_->set_session_name(session_name_);

    control_->set_midi_key_idx(midi_button_id_);
    control_->create_server_road();

    QDialog::close();
}

void ControlProperty::refresh_command(std::uint16_t idx, const CommandItem &item) {
    test_command_->change_item(idx, item);

    emit full_command_changed(test_command_->str().c_str());
}

#pragma endregion Callbacks
