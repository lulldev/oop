#include "car.h"

using namespace std;

bool CCar::IsEngineTurnOn()const
{
    return m_engineIsOn;
}

bool CCar::TurnOnEngine()
{
    if (!m_engineIsOn)
    {
        m_carDirection = stop;
        m_engineIsOn = true;
        return true;
    }
    return false;
}

bool CCar::TurnOffEngine()
{
    if (m_engineIsOn && m_currentGear == 0 &&  m_currentSpeed == 0)
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
            return pair<int, int>(0, 20);
            break;
        case 0:
            return pair<int, int>(0, 0);
            break;
        case 1:
            return pair<int, int>(0, 30);
            break;
        case 2:
            return pair<int, int>(20, 50);
            break;
        case 3:
            return pair<int, int>(30, 60);
            break;
        case 4:
            return pair<int, int>(40, 90);
            break;
        case 5:
            return pair<int, int>(50, 150);
            break;
    }
    
    return pair<int, int>(-1, -1);
}


bool CCar::IsSpeedCorrespondGear(int currentSpeed, int gear)
{
    rangeSpeedMap speedMap = GetAvailableSpeedByGear(gear);
    if (currentSpeed >= speedMap.first && currentSpeed <= speedMap.second)
    {
        return true;
    }
    return false;
}

bool CCar::SetGear(int gear)
{
    
    if (gear >= -1 && gear <= 5)
    {
        if (!IsEngineTurnOn())
        {
            if (gear == 0)
            {
                return true;
            }
        }
        else
        {
            if (GetCurrentSpeed() == 0)
            {
                // на нейтралку
                if (gear == -1 && m_currentGear <= 1)
                {
                    return true;
                }
                
                // на первую с нейтралки
                if (gear == 1 && m_currentGear == -1)
                {
                    return true;
                }
            }
            else
            {
                // на ходу с заднего на 1ую
                if (gear == 0 && m_currentGear == -1 && m_carDirection == stop)
                {
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

int CCar::GetCurrentSpeed()const
{
    return m_currentSpeed;
}

bool CCar::SetSpeed(int speed)
{
    if (IsSpeedCorrespondGear(speed, m_currentGear))
    {
        // направление в зависимости от скорости и передачи
        switch (m_currentGear)
        {
            case -1:
                m_carDirection = back;
                break;
            case 0:
                if (speed == 0)
                {
                    m_carDirection = stop;
                }
                break;
            default:
                m_carDirection = onward;
                break;
        }
        
        m_currentSpeed = speed;
        return true;
    }
    
    return false;
}

