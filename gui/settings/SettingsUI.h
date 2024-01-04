/**
 * @brief Settings UI
 * @details Settings UI encapsulates the behaviour for rendering
 * the settings UI and its associated pages.
 * @author Jun Shao
 */

#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTextArea.h>
#include <unordered_map>
#include "LocationUI.h"

class MainUI;

class SettingsUI : public Wt::WTemplate
{
private:
    std::string username;

public:
    SettingsUI(MainUI *main, string username);
    ~SettingsUI();
};

#endif