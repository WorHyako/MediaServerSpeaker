#pragma once

#include <memory>

#include "spdlog/spdlog.h"

class QWidget;

namespace Mss::Gui::Controls {
	/**
	 * @brief	Creates and logs qt control.
	 *			<p>
	 *			Don't forget to release smart pointer. It will be destroyed otherwise.
	 *
	 * @tparam	TControlType	Control type to create.
	 *
	 * @usage
	 * @code
	 *			auto control = ControlCreator<ControlType>::create(parent);
	 *			control.release();
	 * @endcode
	 *
	 * @author	WorHyako
	 */
	template <typename TControlType>
	class ControlCreator final {
	public:
		/**
		 * @brief Ctor.
		 */
		ControlCreator() noexcept = delete;

		/**
		 * @brief	Creates new control, logs and returns it via smart pointer.
		 *
		 * @return	New control.
		 */
		[[nodiscard]]
		static std::unique_ptr<TControlType> create(QWidget* parent = nullptr) noexcept;

	private:
		/**
		 * @brief	Log creating process.
		 */
		static void log() noexcept;
	};

	template <typename TControlType>
	void ControlCreator<TControlType>::log() noexcept {
		std::stringstream ss;
		ss << "ControlCreator:\n"
				<< "Object "
				<< typeid(TControlType).name()
				<< " was created";
		spdlog::info(ss.str());
	}

	template <typename TControlType>
	std::unique_ptr<TControlType> ControlCreator<TControlType>::create(QWidget* parent) noexcept {
		log();
		return std::make_unique<TControlType>(parent);
	}
}
