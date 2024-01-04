#include "CalculatorUI.h"

using namespace std;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for CalculatorUI, creates the user interface for the calculator, intitalizes fields, 
 * creates interactable buttons.
 * @return nothing
 * @author Jun Shao
 */
CalculatorUI::CalculatorUI() {
    setWindowTitle("Calculator");
	setModal(false);
	setResizable(true);
	setMinimumSize("350", "500");
    contents()->addStyleClass("form-group");

    calc = Calculator();
    first = 0;
    second = 0;
    operand = nullptr;

    WPushButton *backBtn = titleBar()->addNew<WPushButton>();
	backBtn->addStyleClass("btn-close");
	backBtn->setToolTip("Close window", TextFormat::XHTML);
	backBtn->clicked().connect(this, &WDialog::reject);

    input = contents()->addNew<WLineEdit>();
    auto validator = make_shared<WRegExpValidator>("^\\d*\\.?\\d+$");
    input->setValidator(validator);
    input->setStyleClass("bg-dark text-white");
    input->setText("0");

    btnArea = contents()->addNew<WContainerWidget>();
    btnArea->setStyleClass("calculator-keys h-75");

    createOperand("+");
    createOperand("-");
    createOperand("x");
    createOperand("÷");
    createNum("7");
    createNum("8");
    createNum("9");
    createOperand("^");
    createNum("4");
    createNum("5");
    createNum("6");
    createOperand("√");
    createNum("1");
    createNum("2");
    createNum("3");
    createOperand("mod");
    createNum("0");
    createNum(".");

    btns["="] = btnArea->addWidget(make_unique<WPushButton>("="));
    btns["="]->clicked().connect([=] { this->compute(); });

    btns["AC"] = btnArea->addWidget(make_unique<WPushButton>("AC"));
    btns["AC"]->setStyleClass("btn-danger text-white");
    btns["AC"]->clicked().connect([=] { input->setText("0"); });
}

/**
 * @brief Destructor.
 * @details Default destructor for the CalculatorUI class.
 * @return nothing
 * @author Jun Shao
 */
CalculatorUI::~CalculatorUI() {}

/**
 * @brief Appends provided string to input text field.
 * @details Aopends a provided string to the input text field, 
 * which will be a digit from one of the numbered buttons, 
 * if the current contents of the text field is just "0" then 
 * replace the number with the new string instead of appending it.
 * @param s which is a string representing a number from one of the numbered buttons 
 * @return nothing
 * @author Jun Shao
 */
void CalculatorUI::append(string s) {
    if (input->text().toUTF8() == "0") {
        input->setText(s);
    } else {
        input->setText(input->text() + s);
    }
}

/**
 * @brief Contains logic for when an operand button is pressed.
 * @details Function which is called when an operand button is pressed, saves the current input, 
 * clears the input field back to "0", and sets most recent operand variable 
 * to whatever operand button was pressed for later use in compute().
 * @param btn is a string representing the button pressed
 * @return nothing
 * @author Anthony Tam
 */
void CalculatorUI::operate(string btn) {
    first = stod(input->text().toUTF8());
    operand = btns[btn];
    if(operand->text().toUTF8() == "√"){
        first = calc.root(first);
        string inputString = to_string(first);
        inputString.erase(inputString.find_last_not_of('0') + 1, string::npos);
        inputString.erase ( inputString.find_last_not_of('.') + 1, string::npos );
        input->setText(inputString);
    } else {
        input->setText("0");
    }
}

/**
 * @brief Computes the result after the equal sign is pressed.
 * @details Computes the result after the equal sign is pressed, looks at current input and 
 * previous input as well as most recent operand button pressed,
 * @return nothing
 * @author Anthony Tam
 */
void CalculatorUI::compute() {
    if (operand != nullptr) {
        string opStr = operand->text().toUTF8();
        second = stod(input->text().toUTF8());
        cerr << "\n calculating " << first << " " + opStr + " " << second << "\n";
        
        //if statement logics
        if(opStr == "+"){
            first = calc.addition(first,second);
        }
        if(opStr == "-"){
            first = calc.subtraction(first,second);
        }
        if(opStr == "x"){
            first = calc.multiplication(first,second);
        }
        if(opStr == "÷"){
            first = calc.division(first,second);
        }
        if(opStr == "^"){
            first = calc.exponent(first,second);
        }
        string inputString = to_string(first);
        inputString.erase(inputString.find_last_not_of('0') + 1, string::npos);
        inputString.erase ( inputString.find_last_not_of('.') + 1, string::npos );
        input->setText(inputString);
    }
}

/**
 * @brief Creates an operand button
 * @details Creates an operand button using string input for type of button, adds it to UI and 
 * gives it functionality by calling operate() function
 * @param type is a string representing the type of button and its label
 * @return nothing
 * @author Jun Shao
 */
void CalculatorUI::createOperand(string type) {
    btns[type] = btnArea->addWidget(make_unique<WPushButton>(type));
    btns[type]->setStyleClass("btn-warning text-dark");
    btns[type]->clicked().connect([=] { this->operate(type); });
}

/**
 * @brief Creates a number button
 * @details Creates a number button using string input for type of button, adds it to UI and 
 * gives it functionality by calling append() function
 * @param val representing the type of button
 * @return nothing
 * @author Jun Shao
 */
void CalculatorUI::createNum(string val) {
    btns[val] = btnArea->addWidget(make_unique<WPushButton>(val));
    btns[val]->setStyleClass("btn-dark text-white");
    btns[val]->clicked().connect([=] { this->append(val); });
}