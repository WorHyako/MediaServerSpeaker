#pragma once

#include <cstdint>

#include <QWidget>

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @usage
     * @code
     *
     * @endcode
     *
     * @author WorHyako
     */
    enum class ControlType
            : std::uint8_t {
        /**
         * No control
         */
        None = 0b0,

        /**
         * @see Gui::Controls::ManagementTextableButton
         */
        ManagementTextableButton = 0b1,

        /**
         * @see Gui::Controls::ManagementButton
         */
        ManagementButton = 0b10,

        /**
         * @see Gui::Controls::QuickButton
         */
        QuickButton = 0b100,

        /**
         * @see Gui::Controls::QuickTitle
         */
        QuickTitle = 0b1000,

        /**
         * @see Gui::Controls::Table
         */
        Table = 0b10000
    };

    /**
     * @brief
     *
     * @param a
     *
     * @param b
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    inline ControlType operator|(ControlType a, ControlType b) {
        return static_cast<ControlType>(static_cast<int>(a) | static_cast<int>(b));
    }

    /**
     * @brief
     *
     * @param a
     *
     * @param b
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    inline bool operator&(ControlType a, ControlType b) {
        return static_cast<bool>(static_cast<int>(a) & static_cast<int>(b));
    }

    /**
     * @brief
     *
     * @author WorHyako
     */
    class IScope
            : public QWidget {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         */
        explicit IScope(QWidget *parent = nullptr) noexcept;

        /**
         * @brief Dtor.
         */
        ~IScope() noexcept override = default;

        /**
         * @brief
         *
         * @param control
         */
        virtual void addControl(QWidget *control) noexcept = 0;

        /**
         * @brief
         *
         * @param control
         */
        virtual void removeControl(QWidget *control) noexcept = 0;

        /**
         * @brief
         */
        virtual void removeAllControls() noexcept = 0;

        /**
         * @brief
         */
        virtual void loadControls() noexcept = 0;

        /**
         * @brief
         */
        virtual void saveControls() noexcept = 0;

    protected:
        bool _editMode;

        ControlType _controlsType;

        /**
         * @brief
         *
         * @param children
         */
        virtual void editModeChange(bool editMode, QObjectList children) noexcept;

        /**
         * @brief
         *
         * @param controlsType
         */
        virtual void openMenu(QMouseEvent *e, ControlType controlsType) noexcept;

#pragma region Callbacks

        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) noexcept override;

        /**
         * @brief
         *
         * @param e
         */
        void paintEvent(QPaintEvent *e) noexcept override;

#pragma endregion Callbacks
    };
}
