#pragma once

#include <QDialog>

namespace MSS::Gui::Dialogs {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class RenamingDialog
            : public QDialog {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit RenamingDialog(QWidget *parent = nullptr,
                                const std::string &lastName = "");

        /**
         * @brief Dtor.
         */
        ~RenamingDialog() override = default;

    signals:

        /**
         * @brief
         *
         * @param newName
         */
        void renameAccepted(const std::string &newName);
    };
}