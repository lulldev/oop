#pragma once

#include <iostream>
#include <map>

using RangeSpeed = std::pair<int, int>;
using RangeSpeedMap = std::map <int, RangeSpeed>;

enum DirectionMovement
{
    STOP,
    ONWARD,
    BACK
};

class CCar
{
    friend class CCarControl;

public:
    CCar();
    ~CCar() = default;
    
    bool IsEngineTurnOn()const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    
    RangeSpeedMap m_rangeSpeedMap;
    
    RangeSpeed GetAvailableSpeedByGear(int gear);
    bool IsSpeedCorrespondGear(int speed, int gear);
    void UpdateDirection();
    std::string GetDirection()const;
    bool IsGearAllowSpeed(int speed)const;
    
private:
    bool m_engineIsOn;
    DirectionMovement m_carDirection;
    int m_currentSpeed;
    int m_currentGear;

};
