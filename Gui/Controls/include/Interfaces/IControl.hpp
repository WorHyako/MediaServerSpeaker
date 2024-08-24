#pragma once

#include <QWidget>

#include "Components/CommandComponent.hpp"

#include "Menus/ControlContextMenu.hpp"

namespace Mss::Gui::Controls {

    /**
     * @brief
     *
     * @author WorHyako
     */
    class IControl
            : public QWidget,
              public Components::CommandComponent {
    Q_OBJECT

    public:
        /**
         * @brief Ctor.
         */
        explicit IControl(QWidget *parent) noexcept;

        /**
         * @brief Dtor.
         */
        ~IControl() override = default;

        /**
         * @brief
         *
         * @param enable
         */
        virtual void editMode(bool enable) noexcept;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param text
		 */
		virtual void text(std::string text) noexcept = 0;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		virtual std::string text() const noexcept = 0;

#pragma endregion Accessors/Mutators

#pragma region Callbacks
    public:
        /**
         * @brief
         *
         * @param e
         */
        void mousePressEvent(QMouseEvent *e) override;

    public slots:

        /**
         * @brief
         */
        virtual void commandChanged() noexcept = 0;

#pragma endregion Callbacks
	};
}