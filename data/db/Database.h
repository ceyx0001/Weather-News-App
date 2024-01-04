/**
 * @brief Storage and retrieval of SQL data.
 * @details Stores or deletes rows of data found in tables generated
 * by various objects using sqlite3.
 * @author Jun Shao
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <sqlite3.h>
#include <iostream>
#include <algorithm>
#include "../logger/Logger.h"

class Database
{
private:
    sqlite3 *db;
    std::string table;
    std::string keyAttribute;
    const int cols;

public:
    Database(std::string table, std::string keyAttribute, std::vector<std::string> attributes);
    ~Database();
    sqlite3 *getConnection();
    void saveData(std::vector<std::vector<std::string>> dataRow);
    void saveData(std::vector<std::string> row);
    void delData(std::string key);
    std::vector<std::vector<std::string>> readAllUser(std::string username);
    bool exists(std::vector<std::string> arguments);
};

#endif
