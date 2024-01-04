#include "ClockPage.h"

using std::make_unique;
using std::make_shared;
using std::string;
using std::shared_ptr;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for rendering the ClockPage and initializes all members.
 * @param clockName is the name of the clock
 * @param clockFormat is the date format of the clock
 * @return Nothing.
 */
ClockPage::ClockPage(string clockName, string clockFormat) : WTemplate{tr("clockpage")} {
    addFunction("tr", &WTemplate::Functions::tr);

    clocks = bindWidget("clocks", make_unique<WContainerWidget>());

    WPushButton *addClockBtn = bindWidget("addClockBtn", make_unique<WPushButton>("Add"));
    addClockBtn->clicked().connect(this, &ClockPage::showDialog);
    addClockBtn->setStyleClass("mx-5 my-5");

    this->clockName = clockName;
    this->clockFormat = clockFormat;
}

/**
 * @brief Default destructor.
 * @details Default destructor for ClockPage but does nothing
 * @return Nothing.
 */
ClockPage::~ClockPage() {}

/**
 * @brief Get user input for clock.
 * @details Renders a dialog popup that is used for inputting clock information
 * when creating a new clock.
 * @return Nothing.
 */
void ClockPage::showDialog() {
    WDialog* dialog = clocks->addChild(make_unique<WDialog>("Create a New " + clockName));

    WLabel *nameHelp = dialog->contents()->addNew<WLabel>(clockName + " name");
    WLineEdit *edit = dialog->contents()->addNew<WLineEdit>();
    nameHelp->setBuddy(edit);
    WLabel *timeHelp = dialog->contents()->addNew<WLabel>(clockFormat);
    WTimeEdit *te = dialog->contents()->addNew<WTimeEdit>();
    te->setFormat(clockFormat);

    dialog->contents()->addStyleClass("form-group");

    shared_ptr<WValidator> validator = make_shared<WValidator>(true);
    validator->setMandatory(true);
    edit->setValidator(validator);
    te->setValidator(validator);

    WPushButton *save = dialog->footer()->addNew<WPushButton>("Save");
    save->setDefault(true);

    WPushButton *cancel = dialog->footer()->addNew<WPushButton>("Cancel");
    dialog->rejectWhenEscapePressed();

    edit->keyWentUp().connect([=]
                              { save->setDisabled(edit->validate() != ValidationState::Valid); });

    /*
     * Accept the dialog
     */
    save->clicked().connect([=]
                            {
        if (edit->validate() == ValidationState::Valid)
            dialog->accept(); });

    /*
     * Reject the dialog
     */
    cancel->clicked().connect(dialog, &WDialog::reject);

    /*
     * Process the dialog result.
     */
    dialog->finished().connect([=]
                               {
        if (dialog->result() == DialogCode::Accepted) {}
        clocks->removeChild(dialog); });

    dialog->show();
}
