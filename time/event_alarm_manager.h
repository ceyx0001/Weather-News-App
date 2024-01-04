/*
Author: Taimoor Amer

@brief: Event alarm manager header file that has all it's includes, declares the Event_alarm _anager class, and all its member variables 
and functions.

@details: This header file declares the Event_alarm _anager class along with two structures. These structures are Event_alarm, the node for the 
priority queue, and Compare_alarm_time_ascending, the comparator for the priority queue. The priority queue is used to determine which of the alarms
is the closest to arrive, and then checking if it is time to ring that closest alarm yet. The rest of the class enables alarm creation and deletion 
and maintains both the priority queue and a database. The database allows alarms to be repopulated into the priority queue upon program restart.

Date: Tuesday, November 29, 2022
*/

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <queue>
#include <sstream>
#include <thread>
#include <iomanip>
#include <unistd.h>
#include <time.h>
#include "sqlite3.h"

#ifndef EVENT_ALARM_MANAGERCLASS
#define EVENT_ALARM_MANAGERCLASS

struct Event_alarm{
    std::chrono::system_clock::time_point alarm_time;
    std::string message;
    const char* s_alarm_time;

    Event_alarm(std::chrono::system_clock::time_point alarm_time, std::string message, const char* s_alarm_time) : alarm_time(alarm_time), message(message), s_alarm_time(s_alarm_time){
    }
};

struct Compare_alarm_time_ascending {
    bool operator()(Event_alarm const& ea1, Event_alarm const& ea2)
    {
        return ea1.alarm_time > ea2.alarm_time;
    }
};

class Event_alarm_manager
{
    private:

        std::string name_of_table;
        char* error;
        sqlite3* sql_db;
        std::string db_name;
        std::string db_extension;
        std::string sql_create_command;
        std::priority_queue<Event_alarm, std::vector<Event_alarm>, Compare_alarm_time_ascending> pq;

    public:

        Event_alarm_manager();
        void create_event_alarm(const char* alarm_time_s, std::string new_message);
        void delete_event_alarm(const char* alarm_time_s, std::string new_message);
        void check_if_event_alarm_time();
        void refresh_pq_from_db();
        void start();
        ~Event_alarm_manager();
};

#endif
