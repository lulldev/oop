#include "Car.h"

using namespace std;

CCar::CCar()
{
    m_engineIsOn = false,
    m_carDirection = STOP,
    m_currentSpeed = 0,
    m_currentGear = 0;
    
    m_rangeSpeedMap = {
        {-1, {0, 20}},
        {0, {0, 150}},
        {1, {0, 30}},
        {2, {20, 50}},
        {3, {30, 60}},
        {4, {40, 90}},
        {5, {50, 150}}
    };
}

bool CCar::IsEngineTurnOn()const
{
    return m_engineIsOn;
}

bool CCar::TurnOnEngine()
{
    if (!m_engineIsOn)
    {
        m_carDirection = STOP;
        m_engineIsOn = true;
        return true;
    }
    return false;
}

bool CCar::TurnOffEngine()
{
    if (m_engineIsOn && m_currentGear == 0 && m_currentSpeed == 0)
    {
        m_engineIsOn = false;
        return true;
    }
    return false;
}

RangeSpeed CCar::GetAvailableSpeedByGear(int gear)
{
    return m_rangeSpeedMap[gear];
}

bool CCar::IsSpeedCorrespondGear(int currentSpeed, int gear)
{
    RangeSpeed speedRange = GetAvailableSpeedByGear(gear);
    return (currentSpeed >= speedRange.first && currentSpeed <= speedRange.second);
}

bool CCar::IsGearAllowSpeed(int speed)const
{
    if (speed > 0 && m_currentGear == 0)
    {
        return false;
    }
    
    return true;
}

void CCar::UpdateDirection()
{
    if (m_currentSpeed > 0)
    {
        switch (m_currentGear)
        {
            case -1:
                m_carDirection = BACK;
            break;
            case 0:
                    m_carDirection = STOP;
                break;
            default:
                m_carDirection = ONWARD;
                break;
        }
    }
    else
    {
        m_carDirection = STOP;
    }
}

bool CCar::SetGear(int gear)
{
    if (gear >= -1 && gear <= 5)
    {
        if (!IsEngineTurnOn())
        {
            if (gear == 0)
            {
                m_currentGear = gear;
                return true;
            }
        }
        else
        {
            if (m_currentSpeed == 0)
            {
                // на нейтралку
                if (gear == -1 && m_currentGear <= 1)
                {
                    m_currentGear = gear;
                    return true;
                }
                
                // на первую с нейтралки
                if (gear == 1 && m_currentGear == -1)
                {
                    m_currentGear = gear;
                    return true;
                }
            }
            else
            {
                // на ходу с заднего на 1ую
                if (gear == 0 && m_currentGear == -1 && m_carDirection == STOP)
                {
                    m_currentGear = gear;
                    return true;
                }
            }
            
            // на любую при допустимой скорости
            if (IsSpeedCorrespondGear(m_currentSpeed, gear))
            {
                m_currentGear = gear;
                return true;
            }
        }
    }
    
    return false;
}

bool CCar::SetSpeed(int speed)
{
    if (IsSpeedCorrespondGear(speed, m_currentGear) && IsGearAllowSpeed(speed))
    {
        m_currentSpeed = speed;
        UpdateDirection();
        return true;
    }
    
    return false;
}

string CCar::GetDirection()const
{
    switch (m_carDirection) {
        case STOP:
            return "stopped";
            break;
        case ONWARD:
            return "onward";
            break;
        case BACK:
            return "back";
            break;
    }
    
    return "";
}
