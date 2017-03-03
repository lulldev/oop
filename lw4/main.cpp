#include <iostream>
#include <cmath>

#include "ConsoleProgram/ConsoleProgram.h"

using namespace std;

int main(int argc, char* argv[])
{
    string inputString;

    std::vector<shared_ptr<CBody>> bodiesArray;
    ConsoleProgram program(cin, cout, bodiesArray);

    program.ShowHelpUsage();

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