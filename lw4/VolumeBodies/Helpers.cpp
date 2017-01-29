#include "Helpers.h"

double RoundedByDecimals(double number, int decimal)
{
    double devider = decimal * 10;
    return round(number * decimal * 10) / devider;
}