#include "Menus/ControlContextMenu.hpp"

#include "ControlProperty.hpp"

#include "Creators/ControlCreator.hpp"

using namespace Mss::Gui::Controls::Menus;

ControlContextMenu::ControlContextMenu(QWidget *parent) noexcept
	: QMenu(parent) {
	std::ignore = connect(this, SIGNAL(aboutToShow()), this, SLOT(configure()));
	std::ignore = connect(this, SIGNAL(aboutToHide()), this, SLOT(reset()));
}

void ControlContextMenu::configure() {
	auto parent = dynamic_cast<QWidget *>(QMenu::parent());
	if (!parent) {
		return;
	}
	auto propertyDialog = Controls::ControlCreator<Dialogs::ControlProperty>::create(parent);
	std::ignore = connect(propertyDialog.get(), SIGNAL(finished(int)), propertyDialog.get(), SLOT(deleteLater()));

	auto propertyAction = new QAction("Property");
	std::ignore = connect(propertyAction, SIGNAL(triggered(bool)), propertyDialog.get(), SLOT(show()));

	auto deleteAction = new QAction("Delete");
	std::ignore = connect(deleteAction, SIGNAL(triggered(bool)), parent, SLOT(deleteLater()));

	QMenu::addActions({propertyAction, deleteAction});

	std::ignore = propertyDialog.release();
}

void ControlContextMenu::reset() {
	QMenu::clear();
}
