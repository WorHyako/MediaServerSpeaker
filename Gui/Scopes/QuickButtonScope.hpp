#pragma once

#include <vector>

#include <QWidget>

class QGridLayout;

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButtonScope
            : public QWidget {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickButtonScope(QWidget *parent = nullptr);

        /**
         * @brief Dtor.
         */
        ~QuickButtonScope() override = default;

        /**
         * @brief
         *
         * @param e
         */
        void paintEvent(QPaintEvent *e) override;

    private slots:

        /**
         * @brief
         */
        void addButton() noexcept;

    private:
        QGridLayout *_layout;

        std::uint8_t _buttonsCount;
    };
}
