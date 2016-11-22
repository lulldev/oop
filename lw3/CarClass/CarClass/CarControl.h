#pragma once

#include <sstream>
#include <map>
#include <vector>

#include "Car.h"

class CCarControl
{
public:
    CCarControl(CCar & car);
    ~CCarControl() = default;

    bool ReadAndActionCommand(std::istream & input, std::ostream & output);

private:
    void Info();
    bool EngineOn();
    bool EngineOff();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    
    CCar m_car;
    void ActionCommand(std::vector<std::string> args);
    std::stringstream m_output;
};
