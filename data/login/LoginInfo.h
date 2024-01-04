/**
 * @brief User information handling.
 * @details The LoginInfo object contains functionality for handling user data
 * by saving or deleting the data from the database as well as data authentication.
 * @author Jun Shao
 */

#ifndef LOGININFO_H
#define LOGININFO_H

#include <string>
#include <cmath>
#include "../Data.h"

class LoginInfo : public Data
{
private:
    std::string username;
    std::string encryptedPassword;
    Database db;

public:
    LoginInfo(std::string username, std::string password);
    ~LoginInfo();
    bool authenticate();
    bool exists();
    void linkProfile(std::string username);
    void saveData();
    void delData();
    std::string getUsername();
    std::string getPassword();
};

#endif