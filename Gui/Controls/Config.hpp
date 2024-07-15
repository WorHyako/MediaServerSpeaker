#pragma once

#include <string>
#include <vector>
#include <memory>

#include "nlohmann/json.hpp"

class QWidget;

namespace Mss::Gui::Controls {

    using WorQWidgetPtr = std::unique_ptr<QWidget>;
    using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

    /**
     * @brief
     *
     * @usage
     * @code
     *
     * @endcode
     *
     * @tparam      ScopeType
     *
     * @author      WorHyako
     */
    template<class TScopeType>
    class Config final {
    public:
        /**
         * @brief
         *
         * @tparam  ScopeType
         *
         * @param   tabName
         *
         * @return
         */
        [[nodiscard]]
        static WorQWidgetPtrVec load(const std::string &tabName) noexcept;

        /**
         * @brief
         *
         * @tparam ControlType
         *
         * @param json
         *
         * @return
         */
        template<class TControlType>
        [[nodiscard]]
        static WorQWidgetPtrVec loadControls(const nlohmann::json &json) noexcept;

    private:
        /**
         * @brief
         *
         * @param configName
         *
         * @return
         */
        [[nodiscard]]
        static inline nlohmann::json loadConfigFile(const std::string &configName);
    };
}
