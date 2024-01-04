/**
 * @brief Account Management User Interface
 * @details Contains the logic as well as interface for account management, allowing logged in users 
 * to change their password or delete their account.
 * @author Anthony Tam
 */

#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTextArea.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include "../../data/Data.h"

class AccountUI : public Wt::WTemplate {
    private:
        bool okBool;
        bool accountExists();
        Database db;
        Wt::WLineEdit* currentPass;
        Wt::WLineEdit* newPass;
        Wt::WPushButton* okBtn;
        Wt::WPushButton* backBtn;
        Wt::WPushButton* linkBtn;
        Wt::WText* help;
        Wt::WText* title;
        std::string getCurrPass();
        std::string getNewPass();
        std::string username;
        void validatePassword();
        void changing();
        void deleting();

    public:
        AccountUI(std::string username);
        ~AccountUI();
};

#endif