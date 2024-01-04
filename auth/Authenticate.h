/**
 * @brief Authentication of inputted user information.
 * @details Authenticate handles the logic and processes to
 * login users or registering new users after the user submits input.
 * @author Jun Shao
 */

#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <functional>
#include "../data/login/LoginInfo.h"
#include "../gui/login/LoginForm.h"
#include "../gui/main/MainUI.h"
#include "../data/logger/Logger.h"

class Authenticate
{
public:
    ~Authenticate();
    void startAuth();
};

#endif