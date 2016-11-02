#include "car.h"

// todo doc it

bool CCar::IsEngineTurnOn()const
{
    return m_engineIsOn;
}

bool CCar::TurnOnEngine()
{
    if (!m_engineIsOn)
    {
        m_engineIsOn = true;
        return true;
    }
    return false;
}

bool CCar::TurnOffEngine()
{
    if (m_engineIsOn && m_currentGear == 0)
    {
        m_engineIsOn = false;
        return true;
    }
    return false;
}

rangeSpeedMap CCar::GetAvailableSpeedByGear(int gear)
{
    switch(gear)
    {
        case -1:
            return pair<size_t, size_t>(0, 20);
            break;
        case 0:
            return pair<size_t, size_t>(0, 0);
            break;
        case 1:
            return pair<size_t, size_t>(0, 30);
            break;
        case 2:
            return pair<size_t, size_t>(20, 50);
            break;
        case 3:
            return pair<size_t, size_t>(30, 60);
            break;
        case 4:
            return pair<size_t, size_t>(40, 90);
            break;
        case 5:
            return pair<size_t, size_t>(50, 150);
            break;
    }
    
    return pair<size_t, size_t>(-1, -1);
}


bool CCar::IsCurrentSpeedCorrespondGear(size_t currentSpeed, size_t gear)
{
    rangeSpeedMap speedMap = GetAvailableSpeedByGear(gear);
    if (currentSpeed >= speedMap.first && currentSpeed <= speedMap.second)
    {
        return true;
    }
    return false;
}

bool CCar::SetGear(size_t gear)
{
    if (gear >= -1 && gear <= 5)
    {
        if (IsEngineTurnOn() && IsCurrentSpeedCorrespondGear(m_currentSpeed, gear))
        {
            m_currentGear = gear;
            return true;
        }
    }
    return false;
}
