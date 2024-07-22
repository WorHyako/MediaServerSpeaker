#pragma once

#include <string>
#include <vector>
#include <memory>

#include "nlohmann/json.hpp"

class QWidget;

namespace Mss::Gui::Controls::Config {

    using WorQWidgetPtr = std::unique_ptr<QWidget>;
    using WorQWidgetPtrVec = std::vector<WorQWidgetPtr>;

    /**
     * @brief
     *
     * @tparam  ScopeType
     *
     * @param   tabName
     *
     * @return
     *
     * @author WorHyako
     */
    template<class TScopeType>
    [[nodiscard]]
    WorQWidgetPtrVec load(const std::string &tabName) noexcept;

    /**
     * @brief
     *
     * @param tabName
     *
     * @param owner
     *
     * @return
     *
     * @author WorHyako
     */
    template<class TScopeType>
    [[nodiscard]]
    bool save(const std::string &tabName, const QWidget *owner) noexcept;

    /**
     * @brief
     *
     * @tparam ControlType
     *
     * @param json
     *
     * @return
     *
     * @author WorHyako
     */
    template<class TControlType>
    [[nodiscard]]
    WorQWidgetPtrVec loadControls(const nlohmann::json &json) noexcept;

    /**
     * @brief
     *
     * @tparam TControlType
     *
     * @param controls
     *
     * @return
     *
     * @author WorHyako
     */
    template<class TControlType>
    [[nodiscard]]
    nlohmann::json saveControls(WorQWidgetPtrVec controls) noexcept;
}
