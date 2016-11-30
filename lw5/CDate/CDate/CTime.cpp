#include <iostream>
#include <cmath>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "CTime.h"

using namespace std;

CTime::CTime(unsigned timeStamp)
{
    m_timeSeconds = timeStamp;
}

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)
{
    m_validTime = ((hours >= 0) && (hours < 24)) && ((minutes >= 0) && (minutes < 60)) && ((seconds >= 0) && (seconds < 60));
    m_timeSeconds = (hours * 3600) + (minutes * 60) + seconds;
}

unsigned CTime::GetHours()const
{
    return (m_timeSeconds / 3600);
}

unsigned CTime::GetMinutes()const
{
    return (m_timeSeconds / 60) - ((m_timeSeconds / 3600) * 60);
}

unsigned CTime::GetSeconds()const
{
    return (m_timeSeconds % 60);
}

bool CTime::IsValid()const
{
    return m_validTime;
}

string CTime::FormatTime(unsigned timeSeconds)const
{
    string hours = "0" + to_string(timeSeconds / 3600);
    string minutes = "0" + to_string((timeSeconds / 60) - ((timeSeconds / 3600) * 60));
    string seconds = "0" + to_string(timeSeconds % 60);

    return hours.substr(hours.size() - 2) + ":" + minutes.substr(minutes.size() - 2) + ":" + seconds.substr(seconds.size() - 2);
}

unsigned CTime::ParseSecondsFromFormatTime(string & formatTime)
{
    vector<string> splitFormatTime;
    boost::split(splitFormatTime, formatTime, boost::is_any_of(":"));
    
    if (splitFormatTime.size() != 3)
    {
        return -1;
    }
    
    return (stoi(splitFormatTime[0]) * 3600) + (stoi(splitFormatTime[1]) * 60) + stoi(splitFormatTime[2]);
}
