#include "MainUI.h"

using namespace std;
using namespace Wt;

namespace {
    const string OPENSIDEWIDTH = "13%";
    const string CLOSEDSIDEWIDTH = "3.44%";
}

/**
 * @brief Constructor.
 * @details Constructor for MainUI, initializes variables and creates user interface, 
 * adds widgets for displaying weather and news, as well as accessing other modules and 
 * components of the software.
 * @param username is a string represnting the logged in user's username
 * @return nothing
 */
MainUI::MainUI(string username) : WTemplate{tr("main")}, username(username) {
    addStyleClass("content-open");
    sideClosed = false;
    app = WApplication::instance();
    app->internalPathChanged().connect(this, &MainUI::handlePathChange);
    app->setInternalPath("/main");
    
    WLabel *welcome = bindWidget("username", make_unique<WLabel>(username));
    
    WContainerWidget *sidebar = bindWidget("sidebar", make_unique<WContainerWidget>());
    WContainerWidget *backArea = sidebar->addNew<WContainerWidget>();
    backArea->setStyleClass("row d-flex flex-row justify-content-center");

    WPushButton *close = backArea->addNew<WPushButton>();
    close->setStyleClass("btn-close mb-5 mr-5");
    close->clicked().connect([=] {
        if (sideClosed) {
            sideClosed = false;
            sidebar->setWidth(OPENSIDEWIDTH);
            setStyleClass("content-open");
        } else {
            sideClosed = true;
            sidebar->setWidth(CLOSEDSIDEWIDTH);
            setStyleClass("content-closed");
        }
    });

    WPushButton *openListUI = sidebar->addNew<WPushButton>("Notes");
    openListUI->setStyleClass("sidebarbtn");
    openListUI->setIcon("../images/main/list.png");
    openListUI->clicked().connect([=] {
        WDialog* listsWindow = app->root()->addNew<NoteUI>(username);
        listsWindow->show();
    });

    WPushButton *openCalculatorUI= sidebar->addNew<WPushButton>("Calculator");
    openCalculatorUI->setIcon("../images/main/calculator.png");
    openCalculatorUI->setStyleClass("sidebarbtn");
    openCalculatorUI->clicked().connect([=] {
        WDialog* calculatorWindow = app->root()->addNew<CalculatorUI>();
        calculatorWindow->show();
    });

    WPushButton *openConversionUI= sidebar->addNew<WPushButton>("Unit Conversion");
    openConversionUI->setIcon("../images/main/change.png");
    openConversionUI->setStyleClass("sidebarbtn");
    openConversionUI->clicked().connect([=] {
        WDialog* conversionWindow = app->root()->addNew<ConversionUI>();
        conversionWindow->show();
    });

    WPushButton *openClockUI = sidebar->addNew<WPushButton>("Clock");
    openClockUI->setIcon("../images/main/clock.png");
    openClockUI->setStyleClass("sidebarbtn");
    openClockUI->setLink(WLink(LinkType::InternalPath, "/clock"));

    WPushButton *openSettingsUI= sidebar->addNew<WPushButton>("Settings");
    openSettingsUI->setIcon("../images/main/settings.png");
    openSettingsUI->setStyleClass("sidebarbtn");
    openSettingsUI->setLink(WLink(LinkType::InternalPath, "/settings"));

    WPushButton *accountSettingsUI= sidebar->addNew<WPushButton>("Account");
    accountSettingsUI->setIcon("../images/main/accountS.png");
    accountSettingsUI->setStyleClass("sidebarbtn");
    accountSettingsUI->setLink(WLink(LinkType::InternalPath, "/account"));

    weather = bindWidget("weather", make_unique<WeatherUI>(username));

    WContainerWidget *news = bindWidget("news", make_unique<NewsUI>());
}

/**
 * @brief Destructor.
 * @details Default Destructor for MainUI, is empty.
 * @return nothing
 */
MainUI::~MainUI() {}

/**
 * @brief Handle intenral path changes.
 * @details Handler which is called whenever the internal path is changed in the program for certain modules/components, 
 * adds their respective interfaces when the path is changed.
 * @return nothing
 */
void MainUI::handlePathChange() {
    if (app->internalPath() == "/main") {
        this->setHidden(false);
    } else {
        this->setHidden(true);
        if (app->internalPath() == "/clock") {
            app->root()->addNew<ClockUI>();
        } else if (app->internalPath() == "/settings") {
           SettingsUI *main = app->root()->addNew<SettingsUI>(this, username);
        } else if (app->internalPath() == "/account") {
            app->root()->addNew<AccountUI>(username);
        }
    }
}

/**
 * @brief Notify method.
 * @details Notifies weather widget when location is updated.
 * @return nothing
 */
void MainUI::notify() {
    weather = bindWidget("weather", make_unique<WeatherUI>(username));
}