#pragma once

#include "Interfaces/IScope.hpp"

#include <QWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class QuickButtonScope
            : public QWidget,
              public IScope {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         *
         * @param parent
         */
        explicit QuickButtonScope(QWidget *parent = nullptr) noexcept;

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

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;

    private slots:

        /**
         * @brief
         *
         * @param control
         */
        void addControl(QWidget *control) noexcept override;

        /**
         * @brief
         *
         * @param control
         */
        void removeControl(QWidget *control) noexcept override;

        /**
         * @brief
         */
        void removeAllControls() noexcept override;

        /**
         * @brief
         */
        void loadControls() noexcept override;

        /**
         * @brief
         */
        void saveControls() noexcept override;

    private:
        /**
         * @brief
         *
         * @param idx
         */
        void moveAllLeftSince(std::uint8_t idx) noexcept;

        std::uint8_t _buttonsCount;
    };
}
