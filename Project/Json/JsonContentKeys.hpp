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

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getManagementButtonKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getManagementTextableButtonKey() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author  WorHyako
     */
    [[nodiscard]]
    std::string_view getQuickButtonKey() noexcept;
}
