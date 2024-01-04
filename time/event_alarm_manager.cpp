/*
Author: Taimoor Amer

@brief: Event alarm manager implementation file opens up an SQLite database and provides other classes the ability to 
save event alarms onto the database, delete them, and ensures they ring on time.

@details: This header file declares the Event_alarm _anager class along with two structures. These structures are Event_alarm, the node for the 
priority queue, and Compare_alarm_time_ascending, the comparator for the priority queue. The priority queue is used to determine which of the alarms
is the closest to arrive, and then checking if it is time to ring that closest alarm yet. The rest of the class enables alarm creation and deletion 
and maintains both the priority queue and a database. The database allows alarms to be repopulated into the priority queue upon program restart.

Date: Tuesday, November 29, 2022
*/
#include "event_alarm_manager.h"

using std::cout;
using std::endl;

/*
Function name: Event_alarm_manager
@brief: Constructor, initializes all the member variables, opens the SQLite database and creates a table
@details: After opening a database and creating a table if it doesn't already exist, the database is read and any pre-existing data from previous 
times the program was run is pushed onto the priority queue. Then any alarms whose time is already past are deleted rom the database and deleted 
from the priority queue. The missed alarms are sent to be displayed on the UI. Then the thread continues to check whether it is time to ring the 
closest alarm.
Parameters: None
Return: N/A
*/
Event_alarm_manager::Event_alarm_manager()
{
    name_of_table = "alarms";
    db_extension = ".db";
    db_name = name_of_table + db_extension;
    sql_create_command = "CREATE TABLE IF NOT EXISTS \"" + name_of_table + "\"(alarm_time TEXT, message TEXT);";
    sqlite3_open(db_name.c_str(), &sql_db);
    sqlite3_exec(sql_db, sql_create_command.c_str(), NULL, NULL, &error);

    //push any pre-existing data from the database into the priority queue
    refresh_pq_from_db();

    //remove any alarms whose time has already past, and display the missed alarms to the user
    if (!pq.empty())
    {
        auto now_time_point = std::chrono::system_clock::now();
        while (now_time_point >= pq.top().alarm_time)
        {
            std::string missed_alarms = "The following event alarms were missed while Boogle Home was shut off:\n\n";
            missed_alarms += pq.top().message + "\n";
            std::string sql_delete_command = "DELETE FROM \"" + name_of_table + "\" WHERE alarm_time = \"" + pq.top().s_alarm_time + "\" AND message = \"" + pq.top().message + "\" LIMIT 1;"; 
            sqlite3_exec(sql_db, sql_delete_command.c_str(), NULL,NULL,NULL);
            pq.pop();
        }
        //*****send missed_alarms to front_end to display in message box
    }

    //continuously check if it is time for the closest alarm to ring
    while(true)
    {
        check_if_event_alarm_time();
        sleep(1);
    }
}

/*
Function name: create_event_alarm
@brief: Creates an event alarm, saves it into the database, and pushes it onto the priority queue
@details: Creates an event alarm, saves it into the database, and pushes it onto the priority queue. If the alarm message is empty, it gives it the 
standard message of Alarm! If the alarm date is in the past, it sends an error message to be displayed on the UI.
Parameters: char* alarm_time_s - alarm time of type string in the format MMM D YYYY HH:MM:SS
std::string new_message - the message that associated with the alarm
Return: None
*/
void Event_alarm_manager::create_event_alarm(const char* alarm_time_s, std::string new_message)
{
    auto now_time_point = std::chrono::system_clock::now();
    
    if (new_message.empty())
    {
        new_message = "Alarm!";
    }
    
    std::string sql_insert_command = "INSERT INTO \"" + name_of_table + "\"(alarm_time, message) VALUES (\"" + alarm_time_s + "\", \"" + new_message + "\");";
    
    //getting the alarm time and formatting it
    std::stringstream s;
    s << alarm_time_s;
    std::tm alarm_time_tm;
    s >> std::get_time(&alarm_time_tm, "%b %d %Y %H:%M:%S");
    auto alarm_time_point = std::chrono::system_clock::from_time_t(std::mktime(&alarm_time_tm));
    std::time_t alarm_time_t = std::chrono::system_clock::to_time_t(alarm_time_point);
    
    struct tm tm;
    std::istringstream iss("Tue Feb 13 00:26:36 2018");
    iss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    time_t time = mktime(&tm);

    //not allowing an alarm set to a time in the past to be saved
    if (now_time_point >= alarm_time_point)
    {
        //***********call on front-end method to display error message "Your event alarm was for a datetime in the past. Please input a future datetime."
    }
    else
    {
        //writing the alarm time and message to the database and pushing it to the priority queue
        sqlite3_exec(sql_db, sql_insert_command.c_str(), NULL, NULL, &error);
        pq.push(Event_alarm(alarm_time_point, new_message, alarm_time_s));
    }
}

/*
Function name: delete_event_alarm
@brief: Deletes the specified event alarm. 
@details: Deletes the specified event alarm from the database. Empties the priority queue and repopulates it with the updated data in the database.
Parameters: char* alarm_time_s - alarm time of type string in the format MMM D YYYY HH:MM:SS
std::string new_message - the message that associated with the alarm
Return: None
*/
void Event_alarm_manager::delete_event_alarm(const char* alarm_time_s, std::string new_message)
{
    std::string sql_delete_command = "DELETE FROM \"" + name_of_table + "\" WHERE alarm_time = \"" + alarm_time_s + "\" AND message = \"" + new_message + "\" LIMIT 1;"; 
    sqlite3_exec(sql_db, sql_delete_command.c_str(), NULL,NULL,NULL);
    pq = {};
    refresh_pq_from_db();
}

/*
Function name: check_if_event_alarm_time
@brief: Checks if it's time to ring the soonest alarm.
@details: Checks if it's time to ring the soonest alarm, and if it is, then sending it's message to display on the UI, deleting it from the database, 
and popping it from the priority queue.
Parameters: None
Return: None
*/
void Event_alarm_manager::check_if_event_alarm_time()
{
    if (!pq.empty())
    {
        auto now_time_point = std::chrono::system_clock::now();
        if (now_time_point >= pq.top().alarm_time)
        {
            //***********send pq.top().message to front-end to display and sound alarm
            std::string sql_delete_command = "DELETE FROM \"" + name_of_table + "\" WHERE alarm_time = \"" + pq.top().s_alarm_time + "\" AND message = \"" + pq.top().message + "\" LIMIT 1;"; 
            sqlite3_exec(sql_db, sql_delete_command.c_str(), NULL,NULL,NULL);
            pq.pop();
        }
    }
}

/*
Function name: refresh_pq_from_db
@brief: pushes all data from database to priority queue
@details: reads all data from database and then pushes it into priority queue to refresh the priority queue with up to date data after alarm deletion or program restart
Parameters: None
Return: None
*/
void Event_alarm_manager::refresh_pq_from_db()
{
    sqlite3_stmt* sql_select_stmt;

    //reading the saved alarms from the database
    std::string sql_select_command = "SELECT * FROM \"" + name_of_table + "\";";
    sqlite3_prepare(sql_db,sql_select_command.c_str(), -1, &sql_select_stmt, NULL);
    int ret_val = sqlite3_step(sql_select_stmt);
    while (ret_val == SQLITE_ROW)
    {
        //take the alarm time and message, create an event alarm object with them and pushes that object onto the priority queue
        char* alarm_time_s = (char*)sqlite3_column_text(sql_select_stmt, 0);
        char* message = (char*)sqlite3_column_text(sql_select_stmt, 1);
        std::stringstream s;
        s << alarm_time_s;
        std::tm alarm_time_tm;
        s >> std::get_time(&alarm_time_tm, "%b %d %Y %H:%M:%S");
        auto alarm_time_point = std::chrono::system_clock::from_time_t(std::mktime(&alarm_time_tm));
        std::time_t alarm_time_t = std::chrono::system_clock::to_time_t(alarm_time_point);
        pq.push(Event_alarm(alarm_time_point, message, alarm_time_s));

        //go to the next row
        ret_val = sqlite3_step(sql_select_stmt);
    }
    sqlite3_finalize(sql_select_stmt);
}

/*
Function name: ~Event_alarm_manager
@brief: Destructor, closes the SQLite database
@details: Destructor, closes the SQLite database
Parameters: None
Return: N/A
*/
Event_alarm_manager::~Event_alarm_manager()
{
    sqlite3_close(sql_db);
}

void Event_alarm_manager::start()
{
    std::string s = "Nov 29 2022 11:21:10";
    cout << "new thread" << endl;
    create_event_alarm(s.c_str(), "Alarm message");
    while (true)
    {
        check_if_event_alarm_time();
        sleep(1);
    }
}