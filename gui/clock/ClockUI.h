/**
 * @brief Clock UI
 * @details A template object containing behaviour for rendering the Clock UI
 * and its associated pages
 * @author Jun Shao
 */

#ifndef CLOCKUI_H
#define CLOCKUI_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTextArea.h>
#include "ClockPage.h"

class ClockUI : public Wt::WTemplate {
    public:
        ClockUI();
        ~ClockUI();
};

#endif