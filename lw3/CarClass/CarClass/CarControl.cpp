#include "Car.h"
#include "CarControl.h"

using namespace std;

/*
 Info. Выводит состояние двигателя автомобиля, направление движения, скорость и передачу
 EngineOn. Включает двигатель
 EngineOff. Выключает двигатель
 SetGear <передача>. Включает заданную передачу. В случае ошибки сообщает о причине невозможности переключения передачи
 SetSpeed <скорость>. Устанавливает указанную скорость движения. В случае невозможности изменения скорости сообщает о причине невозможности изменить скорость на указанную.
*/

bool CCarControl::HandleCommand()
{
    string commandLine;
    getline(m_input, commandLine);
    istringstream strm(commandLine);
    
    string action;
    strm >> action;
    
    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        return it->second(strm);
    }
    
    return false;
}

bool CCarControl::EngineOn(std::istream & args)
{
    m_car.TurnOnEngine();
    m_output << "Car engine is turn on!" << endl;
    return true;
}

