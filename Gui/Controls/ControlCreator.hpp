#pragma once

#include <memory>

class QWidget;

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     *
     * @tparam TControlType
     *
     * @usage
     * @code
     *
     * @endcode
     *
     * @author WorHyako
     */
    template<typename TControlType>
    class ControlCreator final {
    public:
        /**
         * @brief Ctor.
         */
        ControlCreator() noexcept = delete;

        /**
         * @brief
         *
         * @return
         */
        [[nodiscard]]
        static std::unique_ptr<TControlType> create(QWidget *parent = nullptr) noexcept;

    private:
        /**
         * @brief
         */
        static void log() noexcept;
    };

    template<typename TControlType>
    void ControlCreator<TControlType>::log() noexcept {
        /**
         * Place to log creation process in future
         */
    }

    template<typename TControlType>
    std::unique_ptr<TControlType> ControlCreator<TControlType>::create(QWidget *parent) noexcept {
        log();
        return std::make_unique<TControlType>(parent);
    }
}
