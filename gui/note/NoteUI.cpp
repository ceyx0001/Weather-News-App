#include "NoteUI.h"

using std::make_unique;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for NoteUI that initializes all members and renders the UI.
 * @param username is the session username
 * @return Nothing.
 */
NoteUI::NoteUI(string username) : notes(username)
{
	setWindowTitle("Sticky Notes");
	setModal(false);
	setResizable(true);
	setMinimumSize("350", "500");
	setMaximumSize("1920", "500");
	contents()->setOverflow(Overflow::Scroll, Orientation::Vertical);
	contents()->addStyleClass("form-group");
	footer()->setStyleClass("d-flex flex-row mb-3 mx-3");
	load();

	WPushButton *backBtn = titleBar()->addNew<WPushButton>();
	backBtn->addStyleClass("btn-close");
	backBtn->setToolTip("Close window", TextFormat::XHTML);
	backBtn->clicked().connect([=]
							   {
		notes.delData();
		notes.saveData();
		this->reject(); });

	// adding a new note button linked to prompting user input dialog
	WPushButton *addBtn = footer()->addNew<WPushButton>("+");
	addBtn->setToolTip("New note", TextFormat::XHTML);
	addBtn->setStyleClass("btn btn-primary bg-secondary");
	addBtn->clicked().connect(this, &NoteUI::createDialog);

	// search field that filters notes by type
	search = footer()->addNew<WLineEdit>();
	search->setPlaceholderText("Filter...");
	search->keyWentUp().connect([=]
								{ filter(search->text().toUTF8()); });

	// popup dialog when a new note needs to be created and user input is required
	unique_ptr<WPopupMenu> popupPtr = make_unique<WPopupMenu>();
	popup = popupPtr.get();
	popup->setHideOnSelect(true);
	WPushButton *popupBtn = footer()->addNew<WPushButton>();
	popupBtn->setMenu(move(popupPtr));
	WMenuItem *item = popup->addItem("All");
	item->setCloseable(false);
	item->clicked().connect([=]
							{ search->setText("All"); });
}

/**
 * @brief Default destructor.
 * @details Default destructor for NoteUI but does not do anything.
 * @return Nothing.
 */
NoteUI::~NoteUI() {}

/**
 * @brief Filter notes by type.
 * @details Filters the notes by type and repaints the UI
 * to only show the notes that are of this type.
 * @param type is the note type.
 * @return Nothing.
 */
void NoteUI::filter(string type)
{
	int count = contents()->count();
	// iterate through all of the lists being rendered
	for (int i = 0; i < count; i++)
	{
		WWidget *w = contents()->widget(i);
		if (w->objectName() == type)
		{
			w->show();
		}
		else if (type == "All")
		{
			w->show();
		}
		else
		{
			w->hide();
		}
	}
}

/**
 * @brief Add new note type.
 * @details Adds a new note type to the filter options if a
 * new note was added that has a type not previously seen.
 * @param type is the note type.
 * @return Nothing.
 */
void NoteUI::addType(WLineEdit *typeEdit)
{
	vector<WMenuItem *> items = popup->items();
	bool found = false;
	// iterate through all note types currently seen
	for (WMenuItem *i : items)
	{
		if (i->text() == typeEdit->text().toUTF8())
		{
			found = true;
			break;
		}
	}
	// note type was not found so add it
	if (!found)
	{
		WMenuItem *item = popup->addItem(typeEdit->text().toUTF8());
		item->setCloseable(true);
		// bind a close button to the filter option
		item->clicked().connect([=] { 
			search->setText(typeEdit->text().toUTF8()); 
		});
	}
}

/**
 * @brief Save a note.
 * @details Saves a new Note object and renders it in the note list.
 * @param content is the note content.
 * @param type is the note type.
 * @return Nothing.
 */
void NoteUI::save(string content, string type)
{
	Note note(type, content);
	string date = note.getDateAdded();
	notes.add(note);
	renderNote(note);
}

/**
 * @brief Prompt user input for note.
 * @details Creates the dialog that prompts the user for note information
 * when a new note is meant to be added and assigns its behaviour
 * after the information has been inputted
 * @return Nothing.
 */
void NoteUI::createDialog()
{
	shared_ptr<WValidator> validator = std::make_shared<WValidator>(true);
	hide();

	WDialog *note = contents()->addChild(make_unique<WDialog>());
	note->setWindowTitle("New note");
	note->rejectWhenEscapePressed();
	note->setMovable(false);

	WTextArea *content = note->contents()->addNew<WTextArea>();
	content->setPlaceholderText("Take a note...");
	content->setValidator(validator);

	WLineEdit *type = note->titleBar()->addNew<WLineEdit>();
	type->setPlaceholderText("Type of note");
	type->setValidator(validator);

	WPushButton *save = note->footer()->addNew<WPushButton>("Save");
	save->setDefault(true);
	save->disable();
	WPushButton *cancel = note->footer()->addNew<WPushButton>("Cancel");

	// bind save button to accepting the dialog
	save->clicked().connect([=] {
        if (type->validate() == ValidationState::Valid)
            note->accept(); 
	});

	// bind type input to key released event
	type->keyWentUp().connect([=] { 
		save->setDisabled(type->validate() != ValidationState::Valid); 
	});

	// bind content input to key released event
	content->keyWentUp().connect([=] { 
		save->setDisabled(type->validate() != ValidationState::Valid); 
	});

	cancel->clicked().connect(note, &WDialog::reject);

	// bind dialog to close after input
	note->finished().connect([=] {
		// closing of the dialog
        if (note->result() == DialogCode::Accepted) {
			NoteUI::save(content->text().toUTF8(), type->text().toUTF8());
			bool found = false;
			addType(type);
		}
        removeChild(note);
		show(); 
	});

	note->show();
}

/**
 * @brief Update old note.
 * @details Updates a previously created note in the note list
 * by reprompting for its information and re-rendering the note
 * as well as assigning its behaviour
 * so that it shows the updated contents
 * @param contentLabel is the old Note content
 * @param typeLabel is the old Note type
 * @param dateLabel is the old Note date
 * @return Nothing.
 */
void NoteUI::update(WLabel *contentLabel, WLabel *typeLabel, WLabel *dateLabel)
{
	string date = dateLabel->text().toUTF8();
	string oldContent = contentLabel->text().toUTF8();
	string oldType = typeLabel->text().toUTF8();
	shared_ptr<WValidator> validator = std::make_shared<WValidator>(true);
	hide();

	WDialog *note = contents()->addChild(make_unique<WDialog>());
	note->setWindowTitle("Edit note");
	note->rejectWhenEscapePressed();
	note->setMovable(false);

	WTextArea *content = note->contents()->addNew<WTextArea>();
	content->setText(oldContent);
	content->setValidator(validator);

	WLineEdit *type = note->titleBar()->addNew<WLineEdit>();
	type->setText(oldType);
	type->setValidator(validator);

	unique_ptr<WPopupMenu> popupPtr = make_unique<WPopupMenu>();
	WPopupMenu *popup = popupPtr.get();
	popup->setHideOnSelect(true);
	WPushButton *popupBtn = note->titleBar()->addNew<WPushButton>();
	popupBtn->setMenu(move(popupPtr));

	WPushButton *save = note->footer()->addNew<WPushButton>("Save");
	save->setDefault(true);
	save->disable();
	WPushButton *cancel = note->footer()->addNew<WPushButton>("Cancel");

	save->clicked().connect([=] {
        if (type->validate() == ValidationState::Valid) {
			note->accept(); 
		} 
	});

	type->keyWentUp().connect([=] { 
		save->setDisabled(type->validate() != ValidationState::Valid); 
	});

	content->keyWentUp().connect([=] { 
		save->setDisabled(type->validate() != ValidationState::Valid); 
	});

	cancel->clicked().connect(note, &WDialog::reject);

	note->finished().connect([=] {
        if (note->result() == DialogCode::Accepted) {
			if (oldContent != content->text().toUTF8()) {
				notes.get(date).editDesc(content->text().toUTF8());
				contentLabel->setText(content->text().toUTF8());
			}
			if (oldType != type->text().toUTF8()) {
				notes.get(date).editType(type->text().toUTF8());
				typeLabel->setText(type->text().toUTF8());
			}
		}
        removeChild(note);
		show(); 
	});

	note->show();
}

/**
 * @brief Add new note type.
 * @details Adds a new note type to the filter options if a
 * new note was added that has a type not previously seen.
 * @param type is the note type
 * @return Nothing.
 */
void NoteUI::load()
{
	unordered_map<string, Note> map = notes.getNotes();
	for (auto const &note : map)
	{
		renderNote(note.second);
	}
}

/**
 * @brief Display note.
 * @details Renders a new Note in the sticky notes
 * list UI and assigns the behaviour for clicking on it in the list
 * @param note is the Note to render
 * @return Nothing.
 */
void NoteUI::renderNote(Note note)
{
	WContainerWidget *sticky = contents()->addNew<WContainerWidget>();
	WContainerWidget *top = sticky->addNew<WContainerWidget>();
	WContainerWidget *bot = sticky->addNew<WContainerWidget>();

	sticky->setObjectName(note.getType());
	bot->addStyleClass("d-flex flex-row justify-content-between");
	top->addStyleClass("row");
	sticky->addStyleClass("sticky py-2 my-3 px-2");
	WLabel *contentLabel = top->addNew<WLabel>(note.getDesc());
	contentLabel->addStyleClass("overflow-hidden text-truncate");
	contentLabel->setMaximumSize("500", "50");
	WLabel *typeLabel = top->addNew<WLabel>(note.getType());
	typeLabel->addStyleClass("overflow-hidden text-truncate pt-1");
	typeLabel->setMinimumSize("80", "50");
	typeLabel->setMaximumSize("80", "50");
	WLabel *dateLabel = bot->addNew<WLabel>(note.getDateAdded());
	WPushButton *del = bot->addNew<WPushButton>();
	del->setStyleClass("btn-close");

	// bind delete button to note
	del->clicked().connect([=] { 
		contents()->removeChild(sticky);
		notes.del(note); 
	});

	// bind sticky note container area to update note function
	sticky->clicked().connect([=] { 
		update(contentLabel, typeLabel, dateLabel); 
	});
}