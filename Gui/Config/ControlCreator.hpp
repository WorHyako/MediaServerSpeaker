#pragma once

#include <memory>

namespace Mss::Gui::Config {

    /**
     * @brief
     *
     * @tparam TControlType
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
        static std::unique_ptr<TControlType> create() noexcept;

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
    std::unique_ptr<TControlType> ControlCreator<TControlType>::create() noexcept {
        log();
        return std::make_unique<TControlType>();
    }
}
