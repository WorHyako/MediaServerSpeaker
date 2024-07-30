#include "Scopes/ManagementScope.hpp"

#include "Menus/ScopeContextMenu.hpp"

#include "Controls/ManagementButton.hpp"
#include "Controls/ManagementTextableButton.hpp"
#include "Config/Config.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QCheckBox>

using namespace Mss::Gui::Scopes;
using namespace Mss::Gui::Controls;

ManagementScope::ManagementScope(QWidget *parent) noexcept
        : QWidget(parent) {
    auto checkbox = new QCheckBox(this);
    checkbox->move(100, 350);
    connect(checkbox, &QCheckBox::toggled, [this](bool checked) {
        auto children = QWidget::children();
        std::for_each(std::begin(children), std::end(children), [&checked](QObject *each) {
            auto child = dynamic_cast<MovableBaseControl *>(each);
            if (!child) {
                return;
            }
            child->editMode(checked);
        });
    });
}

void ManagementScope::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(QColor(0xaa, 0xaa, 0xaa));
    painter.drawRoundedRect(0, 0, QWidget::width(), QWidget::height(), 5, 5);

    QWidget::paintEvent(e);
}

void ManagementScope::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::MouseButton::RightButton) {
        auto menu = new Menus::ScopeContextMenu(ControlType::ManagementButton
                                                | ControlType::ManagementTextableButton
                                                | ControlType::Table,
                                                this);
        menu->popup(QWidget::mapToGlobal(e->pos()));
    }

    QWidget::mousePressEvent(e);
}

void ManagementScope::addControl(QWidget *control) noexcept {
    control->setParent(this);
    control->show();
}

void ManagementScope::removeControl(QWidget *control) noexcept {
    control->setParent(nullptr);
    control->deleteLater();
}

void ManagementScope::removeAllControls() noexcept {
    auto children = QWidget::children();
    std::for_each(std::begin(children), std::end(children), [this](QObject *each) {
        auto control = dynamic_cast<MovableBaseControl *>(each);
        if (!control) {
            return;
        }
        removeControl(control);
    });
}

void ManagementScope::loadControls() noexcept {
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
    auto tabName = parentTab->accessibleName().toStdString();

    Config<ManagementScope> config(tabName);
    if (!config.loadConfig()) {
        return;
    }

    auto mbControls = config.loadFromConfig<ManagementButton>();
    auto mtbControls = config.loadFromConfig<ManagementTextableButton>();

    WorQWidgetPtrVec controls;

    controls.reserve(std::size(mbControls) + std::size(mtbControls));
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mbControls)),
                    std::make_move_iterator(std::end(mbControls)));
    controls.insert(std::cend(controls),
                    std::make_move_iterator(std::begin(mtbControls)),
                    std::make_move_iterator(std::end(mtbControls)));

    /**
     * TODO: finish
     */
    std::for_each(std::begin(controls), std::end(controls), [this](auto &each) {
        addControl(each.release());
    });
}

void ManagementScope::saveControls() noexcept {
    const auto &parentTab = dynamic_cast<QWidget *>(QWidget::parent());
    if (!parentTab) {
        return;
    }
    auto tabName = parentTab->accessibleName().toStdString();
    Config<ManagementScope> config(tabName);
    config.addToConfig<ManagementButton>(this);
    config.addToConfig<ManagementTextableButton>(this);
    if (!config.saveConfig()) {
        std::printf("Saving failed\n");
    }
}
