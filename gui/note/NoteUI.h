/**
 * @brief NoteUI
 * @details A template object containing behaviour for rendering the sticky note UI
 * and its associated dialogs.
 * @author Jun Shao
 */

#ifndef NOTEUI_H
#define NOTEUI_H

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WValidator.h>
#include <Wt/WTextArea.h>
#include <Wt/WLabel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <vector>
#include "../../data/note/NoteMap.h"

class NoteUI : public Wt::WDialog
{
private:
    Wt::WLineEdit *search;
    Wt::WPopupMenu *popup;
    NoteMap notes;
    std::string getTypeInput(Wt::WPopupMenu *popup);
    void createDialog();
    void save(std::string note, std::string type);
    void update(Wt::WLabel *contentLabel, Wt::WLabel *typeLabel, Wt::WLabel *dateLabel);
    void addType(Wt::WLineEdit *typeEdit);
    void filter(std::string type);
    void load();
    void renderNote(Note note);

public:
    NoteUI(std::string username);
    ~NoteUI();
};

#endif