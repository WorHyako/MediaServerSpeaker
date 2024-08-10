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
    std::string_view jsonControlKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view jsonHeadKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view jsonTextKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view jsonCommandKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view jsonPositionKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view jsonSizeKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view jsonSessionNameKey() noexcept;
}
