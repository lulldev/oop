#include <iostream>

#include "ConsoleProgram/ConsoleProgram.h"

using namespace std;

int main(int argc, char* argv[])
{
    string inputString;

    cout << "Input information about volume bodies in array\n"
         << "* For example: \n"
         << "sphere <density> <radius>\n"
         << "cone <density> <radius> <height>\n"
         << "parallelepiped <density> <width> <height> <depth>\n"
         << "cylinder <density> <radius> <height>\n"
         << "--------------------------\n" << endl;


    std::vector<shared_ptr<CBody>> bodiesArray;
    ConsoleProgram program(cin, cout, bodiesArray);

    while(getline(cin, inputString))
    {
        try
        {
            program.ProcessInputCommand(inputString);
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << endl;
        }
    }

    program.PrintVolumeBodies();
    program.PrintMaxMassBody();
    program.PrintMinWeightBody();

    return 0;
}