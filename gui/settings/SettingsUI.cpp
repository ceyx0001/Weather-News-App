#include "SettingsUI.h"
#include "../main/MainUI.h"

using std::make_unique;
using std::move;
using namespace Wt;

SettingsUI::SettingsUI(MainUI *main, string username) : WTemplate{tr("menupage")}, username(username) {
    addFunction("tr", &WTemplate::Functions::tr);

    WPushButton *backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
	backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=] {
        this->parent()->removeChild(this);
    });

    WStackedWidget *content = bindWidget("content", make_unique<WStackedWidget>());

    WMenu *sidebar = bindWidget("sidebar", make_unique<WMenu>(content));
    unique_ptr<LocationUI> ui = make_unique<LocationUI>(username);
    ui.get()->attach(main);
    sidebar->addItem("../images/settings/location.png", "Location", move(ui));
    sidebar->setStyleClass("nav nav-pills flex-column");
}

SettingsUI::~SettingsUI() {}