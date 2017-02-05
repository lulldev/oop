#include "Helpers.h"

#include <iostream>

double SimplePow(double number, int power)
{
    double result = number;

    for (int i = 0; i < power - 1; i++)
    {
        result *= number;
    }

    return result;
}