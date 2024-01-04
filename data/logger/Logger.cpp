#include "Logger.h"
using std::cerr;
using std::endl;
using std::string;
using std::vector;

/**
 * @brief Singleton instance.
 * @details Returns the instance of the Logger object that is shared globally.
 * @return The instance of the Logger.
 */
Logger &Logger::instance()
{
    // Scott Meyer's singleton for thread safety
    static Logger instance;
    return instance;
}

/**
 * @brief Default constructor.
 * @details Default constructor for a Logger object that initializes the db connection.
 * @return Nothing.
 */
Logger::Logger()
{
    char *err = 0;
    sqlite3_open("Log.db", &_db); // open connection to db using its handle
    if (err != SQLITE_OK)
    {
        cerr << "Logger - Could not open Database: " << sqlite3_errmsg(_db) << endl;
    }
    else
    {
        cerr << "Logger database opened."
             << endl;
    }
    // create a new sqlite table with the name "app" if it does not exist
    string create_table_cmd = "create table if not exists Logger (timestamp varchar(255), message varchar(255))";
    sqlite3_exec(_db, create_table_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Table construction error: " << sqlite3_errmsg(_db) << endl;
    }
}

/**
 * @brief Default destructor.
 * @details Default destructor for a Logger object that closes the db connection.
 * @return Nothing.
 */
Logger::~Logger()
{
    char *err = 0;
    sqlite3_close(_db); // close connection to "app" db with its handle
    if (err != SQLITE_OK)
    {
        cerr << "Logger - Could not close Data.sql: " << sqlite3_errmsg(_db) << endl;
    }
    else
    {
        cerr << "Logger - Data.db terminated and DB closed."
             << endl;
    }
}

/**
 * @brief Logs a message.
 * @details Inserts a message as a string into the db.
 * @param msg is the message as a string.
 * @return Nothing.
 */
void Logger::log(string msg)
{
    time_t now = time(0);      // gets the current system time
    string time = ctime(&now); // change to c++ string for manipulation
    // remove \n that is generated at the end of a new time_t for formatting
    time.replace(time.length() - 1, time.length(), "\0");

    // insert the log message into the Logger's database
    string insert_cmd = "INSERT INTO LOGGER VALUES (\'" + time + "\', \'" + msg + "\')";
    char *err = 0;
    sqlite3_exec(_db, insert_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Logging error: " << sqlite3_errmsg(_db) << endl;
        cerr << "CMD: " << insert_cmd << endl;
    }
}

/**
 * @brief Load all log messages.
 * @details Loads all log messages as LogMessage objects into a vector.
 * @return A vector containing all stored log messages in the db.
 */
vector<LogMessage> Logger::read_all()
{
    int err = 0;                                  // string pointer used for sqlite errors
    string read_all_cmd = "select * from Logger"; // sqlite statement to get all data from table
    const int len = read_all_cmd.length();
    sqlite3_stmt *stmnt;
    vector<LogMessage> history; // stores found log messages to be returned

    // query against a Logger's database row by row and store the resulting log message
    err = sqlite3_prepare(_db, read_all_cmd.c_str(), len, &stmnt, nullptr);
    if (err != SQLITE_OK)
    {
        cerr << "Could not prepare: " << sqlite3_errmsg(_db) << endl;
    }

    while (sqlite3_step(stmnt) == SQLITE_ROW)
    {
        string time = (const char *)sqlite3_column_text(stmnt, 0);
        string msg = (const char *)sqlite3_column_text(stmnt, 1);
        LogMessage result(time, msg);
        history.push_back(result);
    }

    err = sqlite3_finalize(stmnt);
    if (err != SQLITE_OK)
    {
        cerr << "Could not finalize: " << sqlite3_errmsg(_db) << endl;
    }

    return history;
}