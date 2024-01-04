/**
 * @brief Sticky notes container.
 * @details The NoteMap object holds Note objects and performs
 * data operations such as saving and deleting them from the database.
 * @author Jun Shao
 */

#ifndef NOTEMAP_H
#define NOTEMAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Note.h"
#include "../Data.h"

class NoteMap : public Data
{
private:
    std::string username;
    std::unordered_map<std::string, Note> notes;
    std::unordered_map<std::string, Note> batchToDel;
    Database db;

public:
    NoteMap(std::string username);
    ~NoteMap();
    void saveData();
    void delData();
    void loadData();
    void add(Note list);
    void del(Note list);
    Note get(std::string key);
    std::unordered_map<std::string, Note> getNotes();
};
#endif