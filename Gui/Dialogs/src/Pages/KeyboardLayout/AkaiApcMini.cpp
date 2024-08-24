#include "Pages/KeyboardLayout/AkaiApcMini.hpp"

#include <QGridLayout>

#include "Pages/KeyboardLayout/AkaiApcButton.hpp"

#include "TemplateWrapper/Singleton.hpp"
#include "Midi/MidiKeyboard.hpp"

using namespace Mss::Gui::Dialogs::Pages::KeyboardLayout;

namespace {
	/**
	 * @brief
	 *
	 * @param idx
	 *
	 * @return
	 *
	 * @author WorHyako
	 */
	std::pair<std::uint8_t, std::uint8_t> positionAtIdx(std::uint8_t idx) {
		return {7 - idx / 8, idx % 8};
	}
}

AkaiApcMini::AkaiApcMini(QWidget *parent) noexcept
	: QWidget(parent) {
	auto gridLayout = new QGridLayout;
	QWidget::setLayout(gridLayout);

	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			auto button = new AkaiApcButton(QString::number(column + row * 8));
			button->setAutoFillBackground(true);
			button->setStyleSheet("background-color: rgb(100, 100, 100);");
			gridLayout->addWidget(button, row, column);
		}
	}

	for (int i = 0; i < 64; i++) {
		auto pos = ::positionAtIdx(i);

		auto item = gridLayout->itemAtPosition(pos.first, pos.second);
		auto button = reinterpret_cast<AkaiApcButton *>(item->widget());
		button->setText(QString::number(i));

		connect(button,
				&AkaiApcButton::clicked,
				[idx = i, button]() {
					auto &midiIn = Wor::TemplateWrapper::Singleton<Wor::Midi::MidiKeyboard>::get();
					static int color = 1;
					switch (color) {
						case 0:
							color = 1;
							button->setStyleSheet("background-color: rgb(0, 200, 0);");
							break;
						case 1:
							color = 3;
							button->setStyleSheet("background-color: rgb(200, 0, 0);");
							break;
						case 3:
							color = 5;
							button->setStyleSheet("background-color: rgb(255, 79, 0);");
							break;
						case 5:
							color = 0;
							button->setStyleSheet("background-color: rgb(100, 100, 100);");
					}

					midiIn.send(idx, color);
				});
	}
}
