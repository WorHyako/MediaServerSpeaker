#include "Interfaces/IControl.hpp"

#include "Creators/ControlCreator.hpp"
#include "Menus/ControlContextMenu.hpp"
#include "Midi/MidiRoadMap.hpp"

#include "Wor/Wrappers/Singleton.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

IControl::IControl(QWidget *parent) noexcept
    : QWidget{ parent } {
    QWidget::setObjectName("WorControl");
}

void IControl::create_server_road() const noexcept {
    Backend::Midi::ServerRoad road;
    road.active_command(CommandComponent::command());
    road.set_session_name(CommandComponent::get_session_name());

    auto &road_map{ Wor::Wrappers::Singleton<Backend::Midi::MidiRoadMap>::get() };
    road_map.add_road(MidiComponent::get_midi_key_idx(), road);
}

void IControl::edit_mode(bool enable) noexcept {
    auto children{ QWidget::children() };
    std::ranges::for_each(children, [&enable, this](QObject *each) {
        const auto child{ dynamic_cast<QWidget *>(each) };
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
        MidiComponent::go_midi_road();
        break;
    case Qt::MouseButton::RightButton: {
        auto menu{ ControlCreator<Menus::ControlContextMenu>::create(this) };
        menu->popup(QWidget::mapToGlobal(e->pos()));
        std::ignore = menu.release();
        break;
    }
    default:
        break;
    }
}

void IControl::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

#pragma endregion Callbacks
