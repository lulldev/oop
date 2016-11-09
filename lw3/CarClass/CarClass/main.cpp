#include <iostream>

#include "Car.h"

int main(int argc, const char * argv[])
{
    CCar car;
    car.TurnOffEngine();
    cout << car.SetGear(0) << endl;
}
