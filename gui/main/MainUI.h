/**
 * @brief Main User Interface.
 * @details Contains the main user interface after loggin in, displays news, weather, and buttons for 
 * accessing other components of the program.
 * @author Jun Shao
 */

#ifndef MAINUI_H
#define MAINUI_H

#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include "Observer.h"
#include "../note/NoteUI.h"
#include "../clock/ClockUI.h"
#include "../settings/SettingsUI.h"
#include "../math/CalculatorUI.h"
#include "../math/ConversionUI.h"
#include "../feed/WeatherUI.h"
#include "../feed/NewsUI.h"
#include "../account/AccountUI.h"

class MainUI : public Wt::WTemplate, public Observer {
    private:
        WeatherUI *weather;
        Wt::WApplication *app;
        std::string username;
        bool sideClosed;
        void handlePathChange();
        void notify();

    public:
        MainUI(string username);
        ~MainUI();
};

#endif