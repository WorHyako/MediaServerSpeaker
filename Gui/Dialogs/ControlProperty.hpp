#pragma once

#include <QDialog>

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
         * @param newName
         */
        void renameAccepted(const std::string &newName);
    };
}