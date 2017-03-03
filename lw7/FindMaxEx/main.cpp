#include <iostream>
#include <vector>

using namespace std;

#include "FindMaxEx/FindMaxEx.h"

int main()
{
    vector<int> numberVector = {0, 1, 3, 14, 2, 10};
    int number;

    if (FindMax(numberVector, number, less<int>()))
    {
        cout << "Max element: " << number << endl;
    }
    else
    {
        cout << "No elements" << endl;
    }

/*
    vector<float> floatVector = {10.5, 2.1, 3.1, 8.0};
    float floatNumber;

    if (FindMax(floatVector, floatNumber))
    {
        cout << "Max element: " << floatNumber << endl;
    }
    else
    {
        cout << "No elements";
    }

    vector<string> stringVector = {"apple", "bob", "dog", "cat"};
    string str;

    if (FindMax(stringVector, str))
    {
        cout << "Max element: " << str << endl;
    }
    else
    {
        cout << "No elements";
    }
*/
    return 0;
}