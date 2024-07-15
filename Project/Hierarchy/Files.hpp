#pragma once

#include <string_view>

namespace Mss::System {

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getResourcePath() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getQuickButtonConfigName() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getQuickTitleConfigName() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getManagementButtonConfigName() noexcept;
}
