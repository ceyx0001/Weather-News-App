/**
 * @brief Calculator
 * @details Contains simple calculator operation methods for use in UI, has a command line 
 * based implementation for testing which is commented out 
 * @author Anthony Tam
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <limits>

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator{
    public:
        Calculator();
        ~Calculator();
        double addition(double x, double y);
        double subtraction(double x, double y); 
        double multiplication(double x, double y);
        double division(double x, double y);
        double exponent(double x, double y);
        double square(double x);
        double root(double x);
};

#endif