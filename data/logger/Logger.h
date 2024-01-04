#ifndef LOGGER_H
#define LOGGER_H
/**
 * @brief Manages LogMessage objects
 * @details The Logger object saves log messages to a database
 * and also is able to load all stored log messages from the database.
 * It is a singleton using Scott Meyer's implementation
 * that allows only one instance of the object globally.
 * @author Jun Shao
 */

#include <vector>
#include <sqlite3.h>
#include <iostream>
#include <mutex>
#include <memory>
#include "LogMessage.h"
#include "../db/Database.h"

class Logger
{
public:
    static Logger &instance();
    void log(std::string msg);
    std::vector<LogMessage> read_all();

private:
    sqlite3 *_db;
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

#endif
