#pragma once

#include <string_view>

namespace Mss::System {

    /**
     * @brief
     *
     * @tparam TControlType
     *
     * @return
     */
    template<class TControlType>
    [[nodiscard]]
    constexpr std::string_view getControlKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonHeadKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonTextKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonCommandKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonPositionKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonSizeKey() noexcept;
}
