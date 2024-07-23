#pragma once

#include <memory>

#include <QDialog>
#include <QString>

#include "Command/BaseCommand.hpp"

class QVBoxLayout;

class QHBoxLayout;

namespace Mss::Gui::Controls {
    class BaseControl;
}

namespace Mss::Gui::Dialogs {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class ControlProperty
            : public QDialog {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit ControlProperty(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~ControlProperty() override = default;

    signals:

        /**
         * @brief
         *
         * @param commandStr
         */
        void fullCommandChanged(const QString &commandStr);

    public slots:

        /**
         * @brief
         *
         * @param idx
         *
         * @param item
         */
        void refreshCommand(std::uint16_t idx, const Backend::Command::CommandItem &item);

    private:
        /**
         * @brief
         *
         * @param item
         */
        void addCommandItemHLayout(const Backend::Command::CommandItem &item = {}) noexcept;

        /**
         * @brief
         *
         * @param hLayout
         */
        void removeCommandItemHLayout(QHBoxLayout *hLayout) noexcept;

        /**
         * @brief
         */
        void applyChanged() noexcept;

        Controls::BaseControl *_control;

        QVBoxLayout *_commandLayout;

        std::unique_ptr<Backend::Command::BaseCommand> _testCommand;
    };
}
