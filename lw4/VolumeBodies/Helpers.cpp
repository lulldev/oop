#include "Helpers.h"

using namespace std;

double SimplePow(double number, int power)
{
    double result = number;

    for (int i = 0; i < power - 1; i++)
    {
        result *= number;
    }

    return result;
}

const vector<string> split(const string& targetString, const char& delimiter)
{
    string tmpString("");
    vector<string> resultStringVector;

    for(auto prepareString : targetString)
    {
        if(prepareString != delimiter)
        {
            tmpString += prepareString;
        }
        else if(prepareString == delimiter && tmpString != "")
        {
            resultStringVector.push_back(tmpString);
            tmpString = "";
        }
    }

    if(tmpString != "")
    {
        resultStringVector.push_back(tmpString);
    }

    return resultStringVector;
}