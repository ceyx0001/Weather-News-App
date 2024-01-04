#include "Database.h"

using std::cerr;
using std::endl;
using std::string;
using std::vector;

/**
 * @brief Constructor.
 * @details Constructor for creating a Database object and initializing members.
 * @param table is the table name.
 * @param keyAttribute is the primary key of the table.
 * @param attributes is the list column headers.
 * @return Nothing.
 */
Database::Database(string table, string keyAttribute, vector<string> attributes) : cols(attributes.size()), db(nullptr), table(table), keyAttribute(keyAttribute)
{
    char *err = 0;
    sqlite3_open("Data.db", &db); // open connection to db using its handle
    if (err != SQLITE_OK)
    {
        cerr << "Database - Could not open Database: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cerr << "Database opened." << endl;
    }

    // parsing/formatting the column names as a sql command
    string row; // part of the sql command
    int len = attributes.size();
    for (int i = 0; i < len; i++)
    {
        string s = attributes.back();
        attributes.pop_back();
        row += s + " varchar(255)"; // column size argument
        row += ", ";
    }

    row += "PRIMARY KEY (" + keyAttribute + ")";

    // create a new sqlite table with the name "app" if it does not exist
    string create_table_cmd = "CREATE TABLE IF NOT EXISTS " + table + " (" + row + ")";
    sqlite3_exec(db, create_table_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Table construction error: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cerr << "Table opened: " + table << endl;
    }
}

/**
 * @brief Default destructor.
 * @details Default destructor for a Database object that closes the db connection.
 * @return Nothing.
 */
Database::~Database()
{
    char *err = 0;
    sqlite3_close(db); // close connection to "app" db with its handle
    if (err != SQLITE_OK)
    {
        cerr << "Database - Could not close Data.sql: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cerr << "Database - Data.db terminated and DB closed." << endl;
    }
}

/**
 * @brief Get sqlite3* to db.
 * @details Returns the database connection.
 * @return Nothing.
 */
sqlite3 *Database::getConnection()
{
    return db;
}

/**
 * @brief Save some data to db.
 * @details Saves a data table represented by a 2d vector to an associated table.
 * @param data is the 2d vector containing some data.
 * @return Nothing.
 */
void Database::saveData(vector<vector<string>> data)
{
    char *err = 0;
    string row = ""; // used for the sql command to insert the row of data

    // parsing/formatting the data entries as a sql command
    int rows = data.size();
    int cols = data[0].size();
    // iterate through table represented by 2d vector
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // include each table cell value
            string s = data[i].back();
            data.pop_back();
            row += "\"" + s + "\"";
            if (i < cols - 1)
            {
                row += ", ";
            }
        }

        // insert the rows of data into the database
        string cmd = "INSERT INTO " + table + " VALUES (" + row + ")";
        Logger::instance().log(cmd);
        sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

        if (err != SQLITE_OK)
        {
            cerr << "Database - error executing command: " + cmd << endl
                 << sqlite3_errmsg(db) << endl;
        }
    }
}

/**
 * @brief Save some data to db.
 * @details Saves a data row represented by a vector to an associated table.
 * @param data is the vector containing some data.
 * @return Nothing.
 */
void Database::saveData(vector<string> data)
{
    char *err = 0;
    string row = ""; // used for the sql command to insert the row of data

    // parsing/formatting the data entries as a sql command
    int len = data.size();
    // iterate through columns of the row of data
    for (int i = 0; i < len; i++)
    {
        // include each cell from row
        string s = data.back();
        data.pop_back();
        row += "\"" + s + "\"";
        if (i < len - 1)
        {
            row += ", ";
        }
    }

    // insert the rows of data into the database
    string cmd = "INSERT INTO " + table + " VALUES (" + row + ")"; // check its inserted in correct order
    Logger::instance().log(cmd);
    sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Database - error executing command: " + cmd << endl
             << sqlite3_errmsg(db) << endl;
    }
}

/**
 * @brief Deletes data from db.
 * @details Deletes a row of data from an associated table given the entry's unique key.
 * @param key is the key of the row.
 * @return Nothing.
 */
void Database::delData(string key)
{
    char *err = 0;
    // insert the rows of data into the database
    string cmd = "DELETE FROM " + table + " WHERE " + keyAttribute + "=" + "\"" + key + "\"";
    Logger::instance().log(cmd);
    sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Database - error executing command: " + cmd << endl
             << sqlite3_errmsg(db) << endl;
    }
}

/**
 * @brief Determines existence of data.
 * @details Determines if a row of data exists in an associated table
 * based on some given arguments used for matching.
 * @param arguments is the vector containing conditions to match for.
 * @return Whether or not the row of data exists.
 */
bool Database::exists(vector<string> arguments)
{
    char *err = 0;
    string cond = ""; // used for the sql command as the SELECT condition

    // parsing/formatting the conditions as a sql command
    int len = arguments.size();
    // iterate through arguments
    for (int i = 0; i < len; i++)
    {
        // include each separate argument
        string s = arguments.back();
        arguments.pop_back();
        cond += s;
        if (i < len - 1)
        {
            cond += " AND ";
        }
    }

    string cmd = "SELECT * FROM " + table + " WHERE " + cond;
    sqlite3_stmt *stmnt;

    int result = sqlite3_prepare_v2(db, cmd.c_str(), cmd.length(), &stmnt, nullptr);
    bool found = (sqlite3_step(stmnt) == SQLITE_ROW);
    sqlite3_finalize(stmnt);

    return (found && (result == SQLITE_OK));
}

/**
 * @brief Gets all data from table.
 * @details Loads all rows of data in any table that is associated
 * with the given username and returns a 2d vector representation of it.
 * @param username is the username of the data has to be associated with.
 * @return The data table represented by a 2d vector.
 */
vector<vector<string>> Database::readAllUser(string username)
{
    int err = 0;
    // sqlite statement to get all data from table
    string read_all_cmd = "SELECT * FROM " + table +
                          " WHERE username='" + username + "'";
    const int len = read_all_cmd.length();
    sqlite3_stmt *stmnt;
    vector<vector<string>> data; // stores found log messages to be returned

    // query against a Logger's database row by row and store the resulting log message
    err = sqlite3_prepare(db, read_all_cmd.c_str(), len, &stmnt, nullptr);
    if (err != SQLITE_OK)
    {
        cerr << "Could not prepare: " << sqlite3_errmsg(db) << endl;
    }

    int i = 0;
    while (sqlite3_step(stmnt) == SQLITE_ROW) // iterates rows
    {
        vector<string> row;
        for (int i = 0; i < cols; i++) // iterates columns
        {
            // include each cell of table
            string cell = (const char *)sqlite3_column_text(stmnt, i);
            row.push_back(cell);
        }
        data.push_back(row);
    }

    err = sqlite3_finalize(stmnt);
    if (err != SQLITE_OK)
    {
        cerr << "Could not finalize: " << sqlite3_errmsg(db) << endl;
    }

    return data;
}