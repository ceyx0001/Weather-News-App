/**
 * @brief Assistant Main Class
 * @details Main Assistant Class which the program is run from.
 * @author Jun Shao
 */

#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WString.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrap5Theme.h>
#include "data/logger/Logger.h"
#include "auth/Authenticate.h"

class Assistant: public Wt::WApplication{
    public:
        Assistant(const Wt::WEnvironment &env);
        ~Assistant();
        Wt::WApplication* createApplication(const Wt::WEnvironment &env);
};

#endif