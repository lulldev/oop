#include <iostream>
#include <fstream>

#include "BadWordsFilter/BadWordsFilter.h"

using namespace std;

int main(int argc, const char * argv[])
{
    setlocale(LC_CTYPE, "rus");

    if (argc != 2)
    {
        cout << "Program arguments startup error\n" << "Usage: program <input file>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open())
    {
        cout << "Error open input file: " << argv[1] << endl;
        return 2;
    }

    string fileLine;
    while (getline(inputFile, fileLine))
    {
        ReplaceBadWordsInString(fileLine, cout);
        cout << endl;
    }

    return 0;
}