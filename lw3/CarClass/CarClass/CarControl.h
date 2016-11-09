#include <sstream>

#include "Car.h"

class CCarControl
{
public:
    
    CCarControl(CCar & car, std::istream & input, std::ostream & output);
    bool HandleCommand();

private:
    void Info(std::istream & args);
    bool EngineOn(std::istream & args);
    bool EngineOff(std::istream & args);
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    
private:
    CCar & m_car;
    std::istream & m_input;
    std::ostream & m_output;

    typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;
    
    const ActionMap m_actionMap;
};
