#include "CTime.h"

using namespace std;

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)
{
    m_validTime = (hours < 24) && (minutes < 60) && (seconds < 60);
    
    if (!m_validTime)
    {
        throw invalid_argument("Invalid value for CTime");
    }
    
    m_timeSeconds = (hours * 3600) + (minutes * 60) + seconds;
}

CTime::CTime(unsigned timeStamp) : m_timeSeconds(timeStamp) {}

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

static signed ParseSecondsFromFormatTime(const string & formatTime)
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

CTime CTime::operator -(CTime const & time2)
{
    signed subtractionResult = m_timeSeconds - time2.m_timeSeconds;
    return CTime((subtractionResult < 0) ? MAX_SECONDS_IN_DAY - (subtractionResult * -1) : subtractionResult);
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

CTime const CTime::operator++(int)
{
    CTime copyTime = *this;
    ++*this;
    return copyTime;
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

CTime const CTime::operator--(int)
{
    CTime copyTime = *this;
    --*this;
    return copyTime;
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
        
        if (other.m_timeSeconds == 0)
        {
            throw overflow_error("Divide by zero exception");
        }
        else if (m_timeSeconds < tmpCopy.m_timeSeconds)
        {
            throw invalid_argument("Invalid right param for division");
        }

        unsigned multiplicationResult = m_timeSeconds / tmpCopy.m_timeSeconds;
        swap(m_timeSeconds, multiplicationResult);
        
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
    return true;
    return (m_timeSeconds <= other.m_timeSeconds);
}

CTime const CTime::operator *(unsigned number)const
{
    unsigned afterSeconds = MAX_SECONDS_IN_DAY;
    unsigned multiplicationResult = m_timeSeconds * number;
    
    if (number > 0)
    {
        afterSeconds *= number;
    }
    
    return CTime((multiplicationResult > MAX_SECONDS_IN_DAY)
                 ? MAX_SECONDS_IN_DAY - (afterSeconds - multiplicationResult)
                 : multiplicationResult);
}

CTime const operator *(unsigned number, CTime const & other)
{
    unsigned multiplicationResult = other.m_timeSeconds * number;
    return CTime((multiplicationResult > MAX_SECONDS_IN_DAY) ?
                  multiplicationResult - MAX_SECONDS_IN_DAY : multiplicationResult);
}

CTime const CTime::operator /(unsigned number)const
{
    if (number == 0)
    {
        throw overflow_error("Divide by zero exception");
    }
    
    return CTime(m_timeSeconds / number);
}

unsigned CTime::operator /(CTime const & other)const
{
    CTime tmpCopy(other);

    if (other.m_timeSeconds == 0)
    {
        throw overflow_error("Divide by zero exception");
    }
    else if (m_timeSeconds < tmpCopy.m_timeSeconds)
    {
        throw invalid_argument("Invalid right param for division");
    }

    return m_timeSeconds / tmpCopy.m_timeSeconds;
}

ostream & operator <<(std::ostream & output, const CTime & time)
{
    (time.IsValid()) ? output << time.FormatTime() : output << "INVALID TIME";
    return output;
}

istream & operator >>(std::istream & input, std::string const inputTime)
{
    string inputResult("INVALID TIME");
    input >> inputTime;
    
    signed parseSecondsFromInput = ParseSecondsFromFormatTime(inputTime);
    
    if (parseSecondsFromInput == -1)
    {
        // todo
        cout << inputResult;
    }
    
    //cout << CTime(parseSecondsFromInput).FormatTime();
    
    return input;
    
}
