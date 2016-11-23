#include <iostream>

#include "Car.h"
#include "CarControl.h"

using namespace std;

int main(int argc, const char * argv[])
{
    CCar car;
    CCarControl carControl(car);
    
    while(!cin.eof())
    {
        cout << "Input command >>";
        carControl.ReadAndActionCommand(cin, cout);
    }
    
    return 0;
}
