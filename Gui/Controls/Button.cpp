#include "Controls/Button.hpp"

#include "Controls/ContextMenu.hpp"
#include "Actions/RenameAction.hpp"
#include "Actions/DeleteAction.hpp"

#include <QMouseEvent>

using namespace Mss::Gui::Controls;
using namespace Mss::Gui;

Button::Button(QWidget *parent)
        : QPushButton(parent),
          Components::WidgetTransformComponent(this),
          _isContextMenuEnable(true),
          _contextMenu(nullptr) {
    _contextMenu = new ContextMenu(this);
}

void Button::mouseMoveEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::doTransform(e);

    QPushButton::mouseMoveEvent(e);
}

void Button::mousePressEvent(QMouseEvent *e) {
    const auto button = e->button();
    switch (button) {
        case Qt::MouseButton::LeftButton:
            std::printf("Left ");
            break;
        case Qt::MouseButton::RightButton:
            if (_isContextMenuEnable && _contextMenu) {
                _contextMenu->clear();
                auto renameAction = new Actions::RenameAction(_contextMenu, this);
                auto deleteAction = new Actions::DeleteAction(_contextMenu, this);
                _contextMenu->addActions({ renameAction, deleteAction });
                _contextMenu->popup(mapToGlobal(e->pos()));
            }
            std::printf("Right ");
            break;
        default:
            std::printf("Some ");
            break;
    }

    std::printf("mouse button was pressed on Button with text: %s.\n", QPushButton::text().toStdString().c_str());

    QPushButton::mousePressEvent(e);
}

void Button::mouseReleaseEvent(QMouseEvent *e) {
    emit Components::WidgetTransformComponent::stopTransform(e);

    QPushButton::mouseReleaseEvent(e);
}

void Button::setContextMenuEnable(bool contextMenuEnable) noexcept {
    _isContextMenuEnable = contextMenuEnable;
}
