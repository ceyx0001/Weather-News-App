#include "NoteMap.h"

using std::string;
using std::unordered_map;
using std::vector;

/**
 * @brief Constructor.
 * @details Constructor for a NoteMap object that initialzes all members.
 * @param username is the session username.
 * @return Nothing.
 */
NoteMap::NoteMap(std::string username) : db("Notes", "dateAdded", {"username", "desc", "type", "dateAdded"})
{
    this->username = username;
    loadData();
}

/**
 * @brief Default destructor.
 * @details Default destructor for a NoteMap object but does nothing.
 * @return Nothing.
 */
NoteMap::~NoteMap() {}

/**
 * @brief Save Notes.
 * @details Saves the Note objects in notes to the database.
 * @return Nothing.
 */
void NoteMap::saveData()
{
    for (auto &[key, note] : notes)
    {
        db.saveData({username, note.getDesc(), note.getType(), note.getDateAdded()});
    }
}

/**
 * @brief Delete Notes.
 * @details Deletes the NoteMap's map of Note objects in batchToDel
 * from the database which were intended to be removed by the user.
 * @return Nothing.
 */
void NoteMap::delData()
{
    for (auto &[key, note] : batchToDel)
    {
        db.delData(note.getDateAdded());
    }
}

/**
 * @brief Load Notes.
 * @details Loads into notes the Note objects which were
 * previously stored by the user and found in the database.
 * @return Nothing.
 */
void NoteMap::loadData()
{
    vector<vector<string>> lists = db.readAllUser(username);
    for (const auto &row : lists)
    {
        notes.emplace(row[0], Note(row[1], row[2], row[0]));
    }
}

/**
 * @brief Add Note.
 * @details Adds to notes a new Note.
 * @param note is the Note.
 * @return Nothing.
 */
void NoteMap::add(Note note)
{
    string key = note.getDateAdded();
    notes.emplace(key, note);
}

/**
 * @brief Delete Note.
 * @details Deletes a Note from notes and adds it to batchToDel.
 * @param note is the Note.
 * @return Nothing.
 */
void NoteMap::del(Note note)
{
    string key = note.getDateAdded();
    notes.erase(key);
    batchToDel.emplace(key, note);
}

/**
 * @brief Get Note.
 * @details Returns the Note associated with a key.
 * @param key is the key of the Note.
 * @return The Note associated with the key.
 */
Note NoteMap::get(string key)
{
    return notes.at(key);
}

/**
 * @brief Get all Note.
 * @details Returns all of the Note objects in notes.
 * @return The unordered_map of Note objects in notes.
 */
unordered_map<string, Note> NoteMap::getNotes()
{
    return this->notes;
}