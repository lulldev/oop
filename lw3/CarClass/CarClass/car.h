#include <iostream>
#include <map>

typedef std::pair <int, int> rangeSpeedMap;

enum directionMovement
{
    stop,
    onward,
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
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    int GetCurrentSpeed()const;

    rangeSpeedMap GetAvailableSpeedByGear(int gear);
    bool IsSpeedCorrespondGear(int speed, int gear);//const;
private:
    
    bool m_engineIsOn;
    directionMovement m_carDirection;
    int m_currentSpeed;
    int m_currentGear;
};
