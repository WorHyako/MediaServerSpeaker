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
    std::string_view getQuickScopeConfigName() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getTitlesScopeConfigName() noexcept;

    /**
     * @brief
     *
     * @return
     *
     * @author WorHyako
     */
    [[nodiscard]]
    std::string_view getManagementScopeConfigName() noexcept;
}
