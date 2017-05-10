#include <fstream>
#include "BadWordsFilter/BadWordsFilter.h"

using namespace std;

int main(int argc, const char * argv[])
{
    if (argc != 3)
    {
        cout << "Program arguments startup error\n" << "Usage: program <input file> <output file>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error i/o files: " << argv[1] << endl;
        return 2;
    }

    /*
    string fileLine;
    getline(inputFile, fileLine);
    int lenght;

    try
    {
        lenght = stoi(fileLine);
    }
    catch(...)
    {
        cout << "Error converting number" << endl;
        return 1;
    }

    string s(""), d("");
    ValidBracketsGenerator(outputFile, lenght, s, d, 0);
    */
    return 0;
}