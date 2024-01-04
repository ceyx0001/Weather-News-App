#include "Calculator.h"

using namespace std;

/**
 * @brief Constructor.
 * @details Constructor for Calculator object, is empty.
 * @return nothing
 */
Calculator::Calculator()
{
}

/**
 * @brief Destructor.
 * @details Default Destructor for Calculator object, is empty.
 * @return nothing
 */
Calculator::~Calculator()
{
}

/**
 * @brief Adds two doubles.
 * @details Takes two doubles as input and adds them, returning the sum.
 * @param x is number in double form
 * @param y is number in double form
 * @return sum of two added doubles
 */
double Calculator::addition(double x, double y)
{
    return x + y;
}

/**
 * @brief Divides two doubles.
 * @details Takes two doubles as input and divides the first by the second, returning the quotient.
 * @param x is number in double form
 * @param y is number in double form
 * @return quotient of a double divided by another double
 */
double Calculator::division(double x, double y)
{
    return x / y;
}

/**
 * @brief Raises one double to the power of the other.
 * @details Takes two doubles as input and raises the first to the power of the second, returns the result.
 * @param x is number in double form
 * @param y is number in double form
 * @return result of a double raised to the power of another double
 */
double Calculator::exponent(double x, double y)
{
    return pow(x, y);
}

/**
 * @brief Subtracts two doubles.
 * @details Takes two doubles as input and subtracts the first by the second, returning the difference.
 * @param x is number in double form
 * @param y is number in double form
 * @return difference between two doubles
 */
double Calculator::subtraction(double x, double y)
{
    return x - y;
}

/**
 * @brief Multiplies two doubles.
 * @details Takes two doubles as input and multiplies them, returning the product.
 * @param x is number in double form
 * @param y is number in double form
 * @return product of two doubles
 */
double Calculator::multiplication(double x, double y)
{
    return x * y;
}

/**
 * @brief Finds square root of a number.
 * @details Takes a double as input and finds the square root.
 * @param x is number in double form
 * @return square root of a number
 */
double Calculator::root(double x)
{
    return sqrt(x);
}

/**
 * @brief Finds square of a number.
 * @details Takes a double as input and finds the square.
 * @param x is number in double form
 * @return square of a number
 */
double Calculator::square(double x)
{
    return pow(x, 2);
}

//BELOW HERE IS A COMMAND LINE BASED IMPLEMENTATION OF THE CALCUALTOR FOR PROTOTYPING AND TESTING
// int main(int argc, char *argv[])
// {
//     Calculator calc = Calculator();
//     bool isRun = true;

//     while (isRun)
//     {
//         double num1;
//         int opNum;
//         cout << endl
//              << "Enter a number: ";
//         cin >> num1;

//         // catch bad inputs (non numbers) to avoid infinite loop
//         if (cin.fail())
//         {
//             cout << "ERROR -- You did not enter a number" << endl;
//             cin.clear();
//             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         }
//         else
//         {
//             cout << endl << "List of operations: " << endl
//                  << "1. add " << "2. subtract " << "3. multiply " << "4. divide" << endl
//                  << "5. square" << " 6. power" << " 7. root " << "8. exit" << endl;

//             cout << endl << "Choose an operation (enter the number): ";
//             cin >> opNum;
//             // catch bad inputs (non numbers) to avoid infinite loop
//             if (cin.fail())
//             {
//                 cout << "ERROR -- You did not enter an integer" << endl;
//                 cin.clear();
//                 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             }
//             else
//             {
//                 bool validOp = false;
//                 for (int i = 1; i < 9; i++)
//                 {
//                     if (opNum == i)
//                     {
//                         validOp = true;
//                     }
//                 }
//                 if (validOp == true)
//                 {
//                     if (opNum == 5)
//                     {
//                         // square
//                         cout << "Square of " << num1 << " is: " << calc.square(num1) << endl;
//                     }
//                     else if (opNum == 7)
//                     {
//                         // root
//                         cout << "Root of " << num1 << " is: " << calc.root(num1) << endl;
//                     }
//                     else if (opNum == 8)
//                     {
//                         // exit
//                         exit(1);
//                     }
//                     else
//                     {
//                         int num2;
//                         cout << endl
//                              << "Enter a second number: ";
//                         cin >> num2;

//                         // catch bad inputs (non numbers) to avoid infinite loop
//                         if (cin.fail())
//                         {
//                             cout << "ERROR -- You did not enter a number" << endl;
//                             cin.clear();
//                             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                         }
//                         else
//                         {
//                             switch (opNum)
//                             {
//                             case 1:
//                                 cout << "Sum of " << num1 << " and " << num2 << " is: " << calc.addition(num1, num2) << endl;
//                                 break;
//                             case 2:
//                                 cout << "Difference of " << num1 << " and " << num2 << " is: " << calc.subtraction(num1, num2) << endl;
//                                 break;
//                             case 3:
//                                 cout << "Product of " << num1 << " and " << num2 << " is: " << calc.multiplication(num1, num2) << endl;
//                                 break;
//                             case 4:
//                                 cout << "Quotient of " << num1 << " and " << num2 << " is: " << calc.division(num1, num2) << endl;
//                                 break;
//                             case 6:
//                                 cout << "Power of " << num1 << " and " << num2 << " is: " << calc.exponent(num1, num2) << endl;
//                                 break;
//                             default:
//                                 break;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }