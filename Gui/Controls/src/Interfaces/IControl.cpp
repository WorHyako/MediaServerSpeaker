#include "Interfaces/IControl.hpp"

#include "Creators/ControlCreator.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Backend::Command;

IControl::IControl(QWidget *parent) noexcept
        : QWidget(parent) {
    QWidget::setObjectName("WorControl");
}

void IControl::editMode(bool enable) noexcept {
    auto children = QWidget::children();
    std::for_each(std::begin(children), std::end(children), [&enable, this](QObject *each) {
        auto child = dynamic_cast<QWidget *>(each);
        if (!child) {
            return;
        }
        child->setAttribute(Qt::WA_TransparentForMouseEvents, enable);
    });
}

#pragma region Callbacks

void IControl::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton: {
            auto menu = Controls::ControlCreator<Menus::ControlContextMenu>::create(this);
            menu->popup(QWidget::mapToGlobal(e->pos()));
            std::ignore = menu.release();
            break;
        }
        default:
            break;
    }
}

#pragma endregion Callbacks
