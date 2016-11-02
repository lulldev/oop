#pragma once

#include <iostream>
#include <map>

using namespace std;

typedef std::pair <std::size_t, std::size_t> rangeSpeedMap;

enum directionMovement
{
    stop,
    forward,
    back
};

class CCar
{
public:
    CCar()
    {
        m_engineIsOn = false,
        m_carDirection = stop,
        m_currentSpeed = 0,
        m_currentGear = 0;
    }
    ~CCar() = default;
    
    bool IsEngineTurnOn()const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(size_t gear);
    bool SetSpeed(size_t speed);
    
    // for testing
    rangeSpeedMap GetAvailableSpeedByGear(int gear);
    bool IsCurrentSpeedCorrespondGear(size_t speed, size_t gear);//const;
private:
    
    bool m_engineIsOn;
    directionMovement m_carDirection;
    std::size_t m_currentSpeed;
    std::size_t m_currentGear;
};
