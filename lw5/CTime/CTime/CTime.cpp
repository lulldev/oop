
#include "CTime.h"

using namespace std;

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)
{
    m_validTime = ((hours >= 0) && (hours < 24)) && ((minutes >= 0) && (minutes < 60)) && ((seconds >= 0) && (seconds < 60));
    m_timeSeconds = (hours * 3600) + (minutes * 60) + seconds;
}

CTime::CTime(unsigned timeStamp) : m_timeSeconds(timeStamp)
{
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

string CTime::FormatTime()const
{
    string hours = "0" + to_string(m_timeSeconds / 3600);
    string minutes = "0" + to_string((m_timeSeconds / 60) - ((m_timeSeconds / 3600) * 60));
    string seconds = "0" + to_string(m_timeSeconds % 60);

    return hours.substr(hours.size() - 2) + ":" + minutes.substr(minutes.size() - 2) + ":" + seconds.substr(seconds.size() - 2);
}

unsigned CTime::ParseSecondsFromFormatTime(const string & formatTime)const
{
    vector<string> splitFormatTime;
    boost::split(splitFormatTime, formatTime, boost::is_any_of(":"));
    
    if (splitFormatTime.size() != 3)
    {
        return -1;
    }
    
    return (stoi(splitFormatTime[0]) * 3600) + (stoi(splitFormatTime[1]) * 60) + stoi(splitFormatTime[2]);
}

CTime CTime::operator +(CTime const & time2)
{
    unsigned additionResult = m_timeSeconds + time2.m_timeSeconds;
    return CTime((additionResult > MAX_SECONDS_IN_DAY) ? additionResult - MAX_SECONDS_IN_DAY : additionResult);
}

CTime  CTime::operator -(CTime const & time2)
{
    signed subtractionResult = m_timeSeconds - time2.m_timeSeconds;
    return CTime((subtractionResult < 0) ? MAX_SECONDS_IN_DAY - (subtractionResult * -1) : subtractionResult);
}

CTime const  CTime::operator++(int)
{
    ++m_timeSeconds;
    if (m_timeSeconds >= MAX_SECONDS_IN_DAY)
    {
        m_timeSeconds = m_timeSeconds - MAX_SECONDS_IN_DAY;
    }
    return *this;
}

CTime const  CTime::operator--(int)
{
    signed seconds = m_timeSeconds;
    --seconds;
    if (seconds < 0)
    {
        m_timeSeconds = MAX_SECONDS_IN_DAY - (seconds * -1);
    }
    else
    {
        m_timeSeconds = seconds;
    }
    return *this;
}

CTime & CTime::operator++()
{
    ++m_timeSeconds;
    if (m_timeSeconds >= MAX_SECONDS_IN_DAY)
    {
        m_timeSeconds = m_timeSeconds - MAX_SECONDS_IN_DAY;
    }
    return *this;
}

CTime & CTime::operator--()
{
    signed seconds = m_timeSeconds;
    --seconds;
    if (seconds < 0)
    {
        m_timeSeconds = MAX_SECONDS_IN_DAY - (seconds * -1);
    }
    else
    {
        m_timeSeconds = seconds;
    }
    return *this;
}

CTime & CTime::operator =(CTime const & other)
{
    if (std::addressof(other) != this)
    {
        CTime tmpCopy(other);
        std::swap(m_timeSeconds, tmpCopy.m_timeSeconds);
    }
    return *this;
}

CTime & CTime::operator +=(CTime const & other)
{
    if (std::addressof(other) != this)
    {
        CTime tmpCopy(other);
        unsigned additionSeconds = m_timeSeconds + tmpCopy.m_timeSeconds;
        if (additionSeconds > MAX_SECONDS_IN_DAY)
        {
            additionSeconds -= MAX_SECONDS_IN_DAY;
        }
        swap(m_timeSeconds, additionSeconds);
    }
    return *this;
}

CTime & CTime::operator -=(CTime const & other)
{
    if (addressof(other) != this)
    {
        CTime tmpCopy(other);
        signed subtractionResult = m_timeSeconds - tmpCopy.m_timeSeconds;
        unsigned subtractionUnsignedResult;
        
        if (subtractionResult < 0)
        {
            subtractionUnsignedResult = MAX_SECONDS_IN_DAY - (subtractionResult * -1);
            m_timeSeconds = subtractionUnsignedResult;
        }
        else
        {
            subtractionUnsignedResult = subtractionResult;
            m_timeSeconds = subtractionUnsignedResult;
        }
        
        swap(m_timeSeconds, subtractionUnsignedResult);
    }
    
    return *this;
}

CTime & CTime::operator *=(CTime const & other)
{
    if (std::addressof(other) != this)
    {
        CTime tmpCopy(other);
        unsigned multiplicationResult = m_timeSeconds * tmpCopy.m_timeSeconds;
        swap(m_timeSeconds, multiplicationResult);
    }
    return *this;
}

CTime & CTime::operator /=(CTime const & other)
{
    if (std::addressof(other) != this)
    {
        CTime tmpCopy(other);
        if (tmpCopy.m_timeSeconds > 0 && tmpCopy.m_timeSeconds <= m_timeSeconds)
        {
            unsigned multiplicationResult = m_timeSeconds / tmpCopy.m_timeSeconds;
            swap(m_timeSeconds, multiplicationResult);
        }
    }
    return *this;
}

bool CTime::operator ==(CTime const & other)const
{
    return (m_timeSeconds == other.m_timeSeconds);
}

bool CTime::operator !=(CTime const & other)const
{
    return !(*this == other);
}

bool CTime::operator >(CTime const & other)const
{
    return (m_timeSeconds > other.m_timeSeconds);
}

bool CTime::operator <(CTime const & other)const
{
    return (m_timeSeconds < other.m_timeSeconds);
}

bool CTime::operator >=(CTime const & other)const
{
    return (m_timeSeconds >= other.m_timeSeconds);
}

bool CTime::operator <=(CTime const & other)const
{
    return (m_timeSeconds <= other.m_timeSeconds);
}

CTime const CTime::operator *(unsigned number)const
{
    unsigned multiplicationResult = m_timeSeconds * number;
    return CTime((multiplicationResult > MAX_SECONDS_IN_DAY) ? multiplicationResult - MAX_SECONDS_IN_DAY : multiplicationResult);
}

// todo
//CTime const operator *(CTime const & other)
//{
//    unsigned multiplicationResult = other.GetSeconds() * number;
//    return CTime((multiplicationResult > MAX_SECONDS_IN_DAY) ?
//                  multiplicationResult - MAX_SECONDS_IN_DAY
//                  : multiplicationResult);
//}

CTime const CTime::operator /(unsigned number)const
{
    unsigned divisionResult = m_timeSeconds;
    if (number > 0 )
    {
        divisionResult = m_timeSeconds / number;
    }
    return CTime(divisionResult);
}

unsigned CTime::operator /(CTime const & other)const
{
    CTime tmpCopy(other);
    unsigned divisionResult = m_timeSeconds;
    if (other.m_timeSeconds > 0 && tmpCopy.m_timeSeconds <= m_timeSeconds)
    {
        divisionResult = m_timeSeconds / tmpCopy.m_timeSeconds;
    }
    return divisionResult;
}

//ostream & operator<<(ostream & output, const CTime & time)
//{
//    (time.IsValid()) ? output << time.FormatTime() : output << "INVALID TIME";
//    return output;
//}
//
//istream & operator>>(istream & input, const CTime & time)
//{
//    (time.ParseSecondsFromFormatTime(input))
//}
