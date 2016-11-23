#include <boost/algorithm/string.hpp>

#include <iostream>
#include <vector>

#include "CarControl.h"

using namespace std;

CCarControl::CCarControl(CCar & car)
    : m_car(car)
{
}

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream strStream(str);
    string strTok;
    
    while(getline(strStream, strTok, delimiter))
    {
        internal.push_back(strTok);
    }
    
    return internal;
}

bool CCarControl::ReadAndActionCommand(std::istream & input, std::ostream & output)
{
    string inputCommand;
    vector<string> splitCommand;
    
    getline(input, inputCommand);
    splitCommand = split(inputCommand, ' ');
    output.clear();
    m_output.str("");
    
    if (splitCommand.size() > 0 && splitCommand.size() <= 2)
    {
        ActionCommand(splitCommand);
        output << m_output.str();
        return true;
    }
    
    return false;
}

void CCarControl::ActionCommand(vector<string> args)
{
    if (args[0] == "Info")
    {
        Info();
    }
    else if (args[0] == "EngineOn")
    {
        EngineOn();
    }
    else if (args[0] == "EngineOff")
    {
        EngineOff();
    }
    else if (args[0] == "SetGear")
    {
        string gearParam = args[1];
        if (isdigit(gearParam[0]) || (gearParam[0] == '-' && isdigit(gearParam[1])))
        {
            try
            {
                SetGear(stoi(gearParam));
            }
            catch(...)
            {
                m_output << "Gear number is wrong!\n";
            }
        }
        else
        {
            m_output << "Gear number is wrong!\n";
        }
    }
    else if (args[0] == "SetSpeed")
    {
        string speedParam = args[1];
        if (isdigit(speedParam[0]))
        {
            try
            {
                SetSpeed(stoi(speedParam));
            }
            catch(...)
            {
                m_output << "Speed number is wrong!\n";
            }
        }
        else
        {
            m_output << "Speed number is wrong!\n";
        }
    }
    else
    {
        m_output << "Unknow command\n";
    }
}

void CCarControl::Info()
{
    string engineStatus = (m_car.m_engineIsOn) ? "on" : "off";
    
    m_output << "Information:\nEngine is: " << engineStatus << "\nCurrent gear: " << m_car.m_currentGear << "\nCurrent speed: " << m_car.m_currentSpeed << "\nCurrent direction: " << m_car.GetDirection() << "\n";
}

bool CCarControl::EngineOn()
{
    bool isEngineOn = m_car.TurnOnEngine();
    
    (isEngineOn)
        ? m_output << "Car engine is turn ON!\n"
        : m_output << "Engine already ON!\n";
    
    return isEngineOn;
}

bool CCarControl::EngineOff()
{
    bool isEngineOff = m_car.TurnOffEngine();
    
    (isEngineOff)
        ? m_output << "Car engine is turn OFF!\n"
        : m_output << "Can't OFF engine!\n";
    
    return isEngineOff;
}

bool CCarControl::SetGear(int gear)
{    
    bool isSetGear = m_car.SetGear(gear);
    
    (isSetGear)
        ? m_output << "Set " << gear << " gear is complete!\n"
        : m_output << "Error set input gear\n";

    return isSetGear;
}

bool CCarControl::SetSpeed(int speed)
{
    bool isSetSpeed = m_car.SetSpeed(speed);
    
    (isSetSpeed)
        ? m_output << "Set " << speed << " km/h is complete!\n"
        : m_output << "Error set input speed\n";
    
    return isSetSpeed;
}

