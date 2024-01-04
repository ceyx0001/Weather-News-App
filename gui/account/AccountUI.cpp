#include "AccountUI.h"

using namespace std;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for AccountUI, intializes username from parameter and creates database object, creates the UI using Wt widgets,
 * prepares UI for password changing initially.
 * @param username is the username of the current logged in user
 * @return nothing
 */
AccountUI::AccountUI(string username) : WTemplate{tr("changePass")}, db("LoginInfo", "username", {"username", "encryptedPassword"})
{
    this->username = username;
    addFunction("tr", &WTemplate::Functions::tr);

    // components for username input

    currentPass = bindWidget("currentPass", make_unique<WLineEdit>());
    currentPass->setStyleClass("form-control form-outline bg-dark text-white");
    currentPass->setPlaceholderText("Current Password");
    currentPass->setId("currentPass");

    // components for password input
    newPass = bindWidget("newPass", make_unique<WLineEdit>());
    newPass->setStyleClass("form-control form-outline bg-dark text-white");
    newPass->setPlaceholderText("New Password");
    newPass->setId("newPass");

    // components for form title
    title = bindWidget("title", make_unique<WText>("Change Password"));
    title->setStyleClass("fw-bold");

    // components for text helping the user
    help = bindWidget("help", make_unique<WText>("Please enter your current password and desired new password."));
    help->setStyleClass("text-dark-50 mt-4");

    okBtn = bindWidget("okBtn", make_unique<WPushButton>("Submit"));
    okBtn->setStyleClass("btn-dark text-white btn-outline-secondary");
    okBtn->clicked().connect([=]
                             { validatePassword(); });

    // components for the button changing forms
    backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
    backBtn->setStyleClass("btn-link text-dark-50 fw-bold");
    backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=]
                               { this->parent()->removeChild(this); });

    linkBtn = bindWidget("linkBtn", make_unique<WPushButton>("Delete Account"));
    linkBtn->setStyleClass("btn-link text-dark-50 fw-bold");

    changing();
}

/**
 * @brief Default Destructor.
 * @details Default Destrucor for the AccountUI class.
 * @return nothing
 */
AccountUI::~AccountUI() {}

/**
 * @brief Main logic after pressing submit button.
 * @details Function that is called when the submit button is pressed, contains the main algorithm for both
 * changing passwords and deleting accounts depending on the page it was pressed on.
 * @return nothing
 */
void AccountUI::validatePassword()
{
    if (okBool)
    {
        string currP, newP;
        currP = getCurrPass();
        newP = getNewPass();
        if (accountExists())
        {
            // gets all entries in the logininfo table with the user's username
            vector<vector<string>> data = db.readAllUser(username);
            // cout << data.at(0).at(0) << endl;
            if (data.at(0).at(0) == currP)
            {
                // correct password
                cout << "what" << endl;
                db.delData(username);
                db.saveData({username, newP});
                help->setText("Password Change Succesful.");
            }
            else
            {
                cout << "wha@@t" << endl;
                // wrong password
                help->setText("You entered the wrong password. Please try again.");
            }
            currentPass->setText("");
            newPass->setText("");
        }
    }
    else if (!okBool)
    {
        string currP, newP;
        currP = getCurrPass();
        newP = getNewPass();
        cout << currP << " SSEES  " << newP << endl;
        if (accountExists())
        {
            // gets all entries in the logininfo table with the user's username
            vector<vector<string>> data = db.readAllUser(username);
            // cout << data.at(0).at(0) << endl;
            if (data.at(0).at(0) == currP && data.at(0).at(0) == newP)
            {
                // correct password
                db.delData(username);
                help->setText("Account Deletion Successful.");
                WApplication::instance()->redirect("http://127.0.0.1:9090/");
            }
            else
            {
                // wrong password
                help->setText("Incorrect Password. Please try again.");
            }
            currentPass->setText("");
            newPass->setText("");
        }
    }
}

/**
 * @brief Gets the input from the first text field.
 * @details Accessor method that returns the input from the first text field as a UTF-8 string,
 * in both the password changing form and account deletion form this represents the user's current password.
 * @return the input in the first text field as a string
 */
string AccountUI::getCurrPass()
{
    return currentPass->text().toUTF8();
}

/**
 * @brief Gets the input from the second text field.
 * @details Accessor method that returns the input from the second text field as a UTF-8 string,
 * in the password changing form this is the new desired passsword,
 * in the account deletion form this represents the user's current password again.
 * @return the input in the second text field as a string
 */
string AccountUI::getNewPass()
{
    return newPass->text().toUTF8();
}

/**
 * @brief Checks if the account exists in the database under the given username.
 * @details Function which checks in the database object for any account with the provided username, somewhat
 * redundant given that an account must exist for a user to be logged in and use this function, but
 * checks just in case for freak incidents where the account does not exist.
 * @return whether or not the username is saved with boolean value
 */
bool AccountUI::accountExists()
{
    return db.exists({"username=\"" + username + "\""});
}

/**
 * @brief Changes UI form to Password Change.
 * @details Method which is called to change the UI to the password change form, 
 * sets global variable okBool to true so that verifyPassword() knows the submit 
 * button is being called for password changing, 
 * and changes the link button to go to the delete account form using deleting().
 * @return nothing
 */
void AccountUI::changing()
{
    okBool = true;
    animateHide(WAnimation(AnimationEffect::Fade));

    title->setText("Change Password");
    help->setText("Please enter your current password and then your desired new password.");
    linkBtn->setText("Delete Account");
    linkBtn->clicked().connect([=]
                               { deleting(); });

    animateShow(WAnimation(AnimationEffect::Fade));
}

/**
 * @brief Changes UI form to Account Deletion.
 * @details Method which is called to change the UI to the password change form, 
 * sets global variable okBool to flase so that verifyPassword() knows the submit 
 * button is being called for account deletion, 
 * and changes the link button to go to the password change form using changing().
 * @return nothing
 */
void AccountUI::deleting()
{
    okBool = false;
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Delete Account");
    help->setText("Warning: Account deletion is permanent. Enter your password twice to confirm.");
    linkBtn->setText("Change Password");
    linkBtn->clicked().connect([=]
                               { changing(); });

    animateShow(WAnimation(AnimationEffect::Fade));
}
