#include "LoadAction.hpp"

#include "Config/ControlsConfig.hpp"

#include <QWidget>

using namespace Mss::Gui::Actions;

LoadAction::LoadAction(QObject *parent, QWidget *caller)
        : QAction(parent),
          IAction(caller) {
    QAction::setText("Load");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(execute()));
}

void LoadAction::execute() const noexcept {
    std::string tabName = "tab1";
    auto controls = Config::load(tabName);
    for (auto &each : controls) {
        auto control = each.release();
        control->setParent(IAction::_caller);
        control->show();
    }
}
