#pragma once

#include <cstdint>

class QWidget;

namespace Mss::Gui::Scopes {

    /**
     * @brief
     *
     * @author WorHyako
     */
    enum class ControlType
            : std::uint8_t {
        /**
         * @see Gui::Controls::Button
         */
        ManagementTextableButton = 0b1,
        /**
         * @see
         */
        ManagementButton = 0b10,
        /**
         * @see
         */
        QuickButton = 0b100,
        /**
         * @see
         */
        QuickTitle = 0b1000
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
    class IScope {
    public:
        /**
         * @brief
         *
         * @param control
         */
        [[maybe_unused]]
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
    };
}
