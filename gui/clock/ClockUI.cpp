#include "ClockUI.h"

using std::make_unique;
using namespace Wt;

/**
 * @brief Default constructor.
 * @details Default constructor for rendering the ClockUI
 * @return Nothing.
 */
ClockUI::ClockUI() : WTemplate{tr("menupage")}
{
    addFunction("tr", &WTemplate::Functions::tr);

    WPushButton *backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
    backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=]
                               { this->parent()->removeChild(this); });

    WStackedWidget *content = bindWidget("content", make_unique<WStackedWidget>());

    WMenu *sidebar = bindWidget("sidebar", make_unique<WMenu>(content));
    sidebar->addItem("../images/clock/timer.png", "Timer", make_unique<ClockPage>("Timer", "hh:mm:ss"));
    sidebar->addItem("../images/clock/alarm.png", "Alarm", make_unique<ClockPage>("Alarm", "h:mm:ss AP"));
    sidebar->setStyleClass("nav nav-pills flex-column");
}

/**
 * @brief Default destructor.
 * @details Default destructor for ClockUI but does nothing
 * @return Nothing.
 */
ClockUI::~ClockUI() {}