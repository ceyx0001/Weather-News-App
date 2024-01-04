#include "LoginForm.h"
using std::string;
using std::make_unique;
using std::make_shared;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for LoginForm that initializes all members and renders the login form.
 * @return Nothing.
 */
LoginForm::LoginForm() : WTemplate{tr("login")} {
    addFunction("tr", &WTemplate::Functions::tr);

    // components for username input
    userInput = bindWidget("userInput", make_unique<WLineEdit>());
    userInput->setStyleClass("form-control form-outline bg-dark text-white");
    userInput->setPlaceholderText("Username");
    userInput->setId("userInput");

    // components for password input
    passInput = bindWidget("passInput", make_unique<WLineEdit>());
    passInput->setStyleClass("form-control form-outline bg-dark text-white");
    passInput->setPlaceholderText("Password");
    passInput->setId("passInput");

    // components for input validation
    auto validator = make_shared<WValidator>(true);
    userInput->setValidator(validator);
    passInput->setValidator(validator);

    // components for form title
    title = bindWidget("title", make_unique<WText>("Login"));
    title->setStyleClass("fw-bold");

    // components for text helping the user
    help = bindWidget("help", make_unique<WText>("Please fill in your information."));
    help->setStyleClass("text-dark-50 mt-4");

    // components for the submission button
    okBtn = bindWidget("okBtn", make_unique<WPushButton>("Submit"));
    okBtn->setStyleClass("btn-dark text-white btn-outline-secondary");

    // components for the button changing forms
    linkBtn = bindWidget("linkBtn", make_unique<WPushButton>("Register"));
    linkBtn->setStyleClass("btn-link text-dark-50 fw-bold");
    
    // components for text helping to navigate the user
    bottomTxt = bindWidget("bottomTxt", make_unique<WText>("New here?"));
    bottomTxt->setStyleClass("mt-5");

    // change the form to login
    logging();
}

/**
 * @brief Destructor.
 * @details Destructor for LoginForm but does nothing.
 * @return Nothing.
 */
LoginForm::~LoginForm() {}


/**
 * @brief Get username input.
 * @details Returns the currently inputted username as string.
 * @return The text of the currently inputted username.
 */
string LoginForm::getUserInput() {
    return userInput->text().toUTF8();
}

/**
 * @brief Get password input.
 * @details Returns the currently inputted password as string.
 * @return The text of the currently inputted password.
 */
string LoginForm::getPassInput() {
    return passInput->text().toUTF8();
}

/**
 * @brief Get submit button.
 * @details Returns a pointer to the submit button.
 * @return The pointer to the submit button.
 */
WPushButton *LoginForm::getOkBtn() {
    return okBtn;
}

/**
 * @brief Get title.
 * @details Returns title of the current variaton of the login form.
 * @return The title of the current form.
 */
string LoginForm::getTitle() {
    return title->text().toUTF8();
}

/**
 * @brief Get help text.
 * @details Returns a pointer to the help text on the form.
 * @return The pointer to the help text.
 */
WText* LoginForm::getHelp() {
    return help;
}

/**
 * @brief Change form to login.
 * @details Changes the form to logging in and renders it.
 * @return Nothing.
 */
void LoginForm::logging() {
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Login");
    help->setText("Please fill in your information.");
    linkBtn->setText("Register");
    bottomTxt->setText("New here?");
    linkBtn->clicked().connect(this, &LoginForm::registering);
    animateShow(WAnimation(AnimationEffect::Fade));
}

/**
 * @brief Change form to register.
 * @details Changes the form to registering a new user and renders it.
 * @return Nothing.
 */
void LoginForm::registering() {
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Register");
    help->setText("Please fill in your information.");
    linkBtn->setText("Login");
    bottomTxt->setText("Returning?");
    linkBtn->clicked().connect(this, &LoginForm::logging);
    animateShow(WAnimation(AnimationEffect::Fade));
}