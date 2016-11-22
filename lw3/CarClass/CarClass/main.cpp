#include <iostream>

#include "Car.h"
#include "CarControl.h"

using namespace std;

int main(int argc, const char * argv[])
{
    string inputCommand;

    CCar car;
    CCarControl carControl(car);
    
    do
    {
        cout << "Input command >>";
    }
    while (carControl.ReadAndActionCommand(cin, cout));
    
    return 0;
}
