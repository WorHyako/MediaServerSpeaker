#include "QuickButtonScope.hpp"

#include "Config.hpp"
#include "Controls/QuickButton.hpp"

#include <QGridLayout>
#include <QSpacerItem>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

namespace {

	/**
	 * @brief
	 */
	constexpr std::uint8_t rowMax = 5;

	/**
	 * @brief
	 */
	constexpr std::uint8_t columnMax = 6;

	/**
	 * @brief
	 *
	 * @param idx
	 *
	 * @return
	 *
	 * @author WorHyako
	 */
	QPoint calculateButtonPosition(std::size_t idx) {
		std::uint8_t row = idx / (::columnMax - 1);
		std::uint8_t column = idx % ::rowMax;

		return {row, column};
	}
}

QuickButtonScope::QuickButtonScope(QWidget *parent) noexcept
        : IScope(parent),
          _buttonsCount(0) {
    _controlsType = ControlType::QuickButton;
    QWidget::move(1, 1);

	auto layout = new QGridLayout;
	QWidget::setLayout(layout);
	layout->setSpacing(2);

	for (std::uint8_t i = 0; i < ::rowMax * ::columnMax; i++) {
		auto [row, column] = ::calculateButtonPosition(i);
		layout->addWidget(new QWidget, row, column);
		//        std::printf("Kids count - %lli\n", layout->children().size());
	}
}

void QuickButtonScope::addControl(QWidget *control) noexcept {
	if (_buttonsCount >= (::rowMax * ::columnMax - 1)) {
		control->deleteLater();
		return;
	}
	auto layout = QWidget::layout();
	auto nextCell = layout->itemAt(_buttonsCount)->widget();

	nextCell = layout->replaceWidget(nextCell, control, Qt::FindChildOption::FindDirectChildrenOnly)->widget();
	nextCell->deleteLater();

	connect(control,
			&QWidget::destroyed,
			[this](QObject *t) {
				removeControl(dynamic_cast<QWidget *>(t));
			});

    _buttonsCount++;
}

void QuickButtonScope::removeControl(QWidget *control) noexcept {
	auto layout = QWidget::layout();
	std::uint8_t idx = layout->indexOf(control);
	auto item = layout->itemAt(idx);
	item->widget()->deleteLater();
	control->deleteLater();

	layout->update();

	_buttonsCount--;
}

void QuickButtonScope::removeAllControls() noexcept {
	auto allControls = QWidget::layout()->children();
	std::for_each(std::begin(allControls),
				  std::end(allControls),
				  [this](QObject *each) {
					  auto control = dynamic_cast<QWidget *>(each);
					  if (!control) {
						  return;
					  }
					  removeControl(control);
				  });
}

void QuickButtonScope::loadControls() noexcept {
	const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
	if (!parentTab) {
		return;
	}
	/**
	 * TODO: first thread
	 */
	removeAllControls();

	/**
	 * TODO: second thread
	 */
	std::string tabName(parentTab->accessibleName().toUtf8().constData());
	Config<QuickButtonScope> config(tabName);
	if (!config.loadConfig()) {
		return;
	}
	auto controls = config.loadFromConfig<QuickButton>();

	/**
	 * TODO: finish
	 */
	std::for_each(std::begin(controls),
				  std::end(controls),
				  [this](auto &each) {
					  addControl(each.release());
				  });
}

void QuickButtonScope::saveControls() noexcept {
	const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
	if (!parentTab) {
		return;
	}
	std::string tabName(parentTab->accessibleName().toUtf8().constData());
	Config<QuickButtonScope> config(tabName);
	config.addToConfig<QuickButton>(this);
	if (!config.saveConfig()) {
		std::printf("Error in saving process.\n");
	}
}

void QuickButtonScope::moveAllLeftSince(std::uint8_t idx) noexcept {
	auto layout = QWidget::layout();
	for (std::uint8_t i = idx; i < _buttonsCount - 1; ++i) {
		auto current = layout->takeAt(i);
		auto next = layout->takeAt(i + 1);
		auto temp = current;
	}
}

#pragma region Callbacks

void QuickButtonScope::editModeChange(bool toggled) {

}

void QuickButtonScope::mousePressEvent(QMouseEvent *e) noexcept {
    IScope::mousePressEvent(e);
}

#pragma endregion Callbacks
