#pragma once

#include <string_view>

namespace Mss::System {

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
    std::string_view getJsonCanMoveKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getJsonCanResizeKey() noexcept;

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
