#include "Helpers.h"

#include <iostream>

double RoundedByDecimals(double number, int decimal)
{
    double devider = decimal * 10;
    return round(number * decimal * 10) / devider;
}

double SimplePow(double number, int power)
{
    double result = number;

    for (int i = 0; i < power - 1; i++)
    {
        result *= number;
    }

    return result;
}