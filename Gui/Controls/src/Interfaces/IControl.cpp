#include "Interfaces/IControl.hpp"

#include "Creators/ControlCreator.hpp"
#include "Menus/ControlContextMenu.hpp"

#include <QMouseEvent>
#include <Wor/Wrappers/Singleton.hpp>

#include "Midi/MidiRoadMap.hpp"

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

IControl::IControl(QWidget *parent) noexcept
	: QWidget(parent) {
	QWidget::setObjectName("WorControl");
}

void IControl::createServerRoad() noexcept {
	Backend::Midi::ServerRoad road;
	road.activeCommand(CommandComponent::command());
	road.sessionName(CommandComponent::sessionName());

	auto &roadMap = Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get();
	roadMap.addRoad(MidiComponent::midiKeyIdx(), road);
}

void IControl::editMode(bool enable) noexcept {
	auto children = QWidget::children();
	std::ranges::for_each(children,
						  [&enable, this](QObject *each) {
							  const auto child = dynamic_cast<QWidget *>(each);
							  if (!child) {
								  return;
							  }
							  child->setAttribute(Qt::WA_TransparentForMouseEvents, enable);
						  });
}

#pragma region Callbacks

void IControl::mousePressEvent(QMouseEvent *e) {
	switch (e->button()) {
		case Qt::MouseButton::LeftButton:
			break;
		case Qt::MouseButton::RightButton: {
			auto menu = ControlCreator<Menus::ControlContextMenu>::create(this);
			menu->popup(QWidget::mapToGlobal(e->pos()));
			std::ignore = menu.release();
			break;
		}
		default:
			break;
	}
}

#pragma endregion Callbacks
