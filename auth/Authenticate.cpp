#include "Authenticate.h"

using std::cerr;
using std::endl;
using std::string;
using Wt::WApplication;

/**
 * @brief Default destructor.
 * @details Default destructor for deleting an Authenticate object
 * but does not do anything.
 * @return Nothing.
 */
Authenticate::~Authenticate() {}

/**
 * @brief Simulate authentication behaviour.
 * @details Gets user information from input and authenticates or registers.
 * @return Nothing.
 */
void Authenticate::startAuth()
{
    WApplication *app = WApplication::instance();
    LoginForm *f = app->root()->addNew<LoginForm>();

    // operate on user input and start the authentication process
    auto verify = [f, app]
    {
        string username = f->getUserInput();
        string password = f->getPassInput();
        LoginInfo info(username, password);

        string page = f->getTitle();
        bool exists = info.exists(); // determines if the user exists

        // determine if the user is registering or logging in
        if (exists && page == "Login")
        {
            cerr << "Authenticate: checking password." << endl;
            if (info.authenticate())
            {
                cerr << "Authenticate: password correct." << endl;
                app->root()->removeWidget(f);
                app->root()->addNew<MainUI>(username);
                cerr << "started session for" + username << endl;
                Logger::instance().log(username + " started a session.");
            }
            else
            {
                f->getHelp()->setText("Please check that your username or password is correct.");
            }
        }
        else if (exists && page == "Register")
        {
            f->getHelp()->setText("That username already exists!");
        }
        else if (!exists && page == "Login")
        {
            f->getHelp()->setText("Username doesn't exist.");
        }
        else if (!exists && page == "Register")
        {
            info.saveData();
            f->getHelp()->setText("Registration complete!");
        }
    };

    f->getOkBtn()->clicked().connect(verify); // bind function with submit button
}