/**
 * @brief Messages with timestamps.
 * @details The LogMessage object holds a message as a string
 * and a timestamp as a string.
 * @author Jun Shao
 */

#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <string>

class LogMessage
{
private:
    std::string msg, time;

public:
    LogMessage(std::string new_time, std::string new_msg);
    ~LogMessage();
    std::string getMessage();
    std::string getTime();
};

#endif
