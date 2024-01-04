/**
 * @brief Sticky note.
 * @details The Note object encapsulates the behaviour and state
 * that represents what a sticky note is generally.
 * @author Jun Shao
 */

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <unordered_map>

class Note
{
private:
    std::string type;
    std::string desc;
    std::string dateAdded;

public:
    Note(std::string type, std::string desc);
    Note(std::string type, std::string desc, std::string dateAdded);
    ~Note();
    std::string getDateAdded();
    std::string getDesc();
    std::string getType();
    void editDesc(std::string newDesc);
    void editType(std::string newType);
};

#endif