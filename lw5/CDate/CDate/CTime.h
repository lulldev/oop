#define MAX_SECONDS_IN_DAY 86400

// моделирует время суток, задаваемое количеством часов (0-23), минут (0-59) и
// секунд (0-59)
class CTime
{
public:
    // храним время в секундах
    unsigned m_timeSeconds;

    // инициализирует время заданным количеством часов, минут и секунд
    CTime(unsigned hours, unsigned minutes, unsigned seconds = 0);
    
    // инициализирует время количеством секунд после полуночи
    CTime(unsigned timeStamp = 0);
    
    // возвращает количество часов
    unsigned GetHours()const;
    
    // возвращает количество минут
    unsigned GetMinutes()const;
    
    // возвращает количество секунд
    unsigned GetSeconds()const;
    
    // возвращает информацию о корректности времени.
    // Например, после вызова конструктора CTime time(99, 32, 83);
    //	метод time.IsValid() должен возвращать false
    bool IsValid()const;
    
    // конвертирует заданные секунды в формат h:m:s
    std::string FormatTime(unsigned timeSeconds)const;
    
    // считывыет из строки формата h:m:s числовое значение секунд
    unsigned ParseSecondsFromFormatTime(std::string & formatTime);
    
    CTime const operator +(CTime const & time2)const
    {
        unsigned additionResult = m_timeSeconds + time2.m_timeSeconds;
        return CTime((additionResult > MAX_SECONDS_IN_DAY) ? additionResult - MAX_SECONDS_IN_DAY : additionResult);
    }
    
    CTime const operator -(CTime const & time2)const
    {
        signed subtractionResult = m_timeSeconds - time2.m_timeSeconds;
        return CTime((subtractionResult < 0) ? MAX_SECONDS_IN_DAY - (subtractionResult * -1) : subtractionResult);
    }
    
    CTime& operator++()
    {
        ++m_timeSeconds;
        if (m_timeSeconds >= MAX_SECONDS_IN_DAY)
        {
            m_timeSeconds = m_timeSeconds - MAX_SECONDS_IN_DAY;
        }
        return *this;
    }
    
    CTime & operator--()
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
    
    CTime const operator++(int)
    {
        ++m_timeSeconds;
        if (m_timeSeconds >= MAX_SECONDS_IN_DAY)
        {
            m_timeSeconds = m_timeSeconds - MAX_SECONDS_IN_DAY;
        }
        return *this;
    }
    
    CTime const operator--(int)
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
    
    CTime & operator =(CTime const & other)
    {
        if (std::addressof(other) != this)
        {
            CTime tmpCopy(other);
            std::swap(m_timeSeconds, tmpCopy.m_timeSeconds);
        }
        return *this;
    }
    
    CTime & operator +=(CTime const & other)
    {
        if (std::addressof(other) != this)
        {
            CTime tmpCopy(other);
            unsigned additionSeconds = m_timeSeconds + tmpCopy.m_timeSeconds;
            if (additionSeconds > MAX_SECONDS_IN_DAY)
            {
                additionSeconds -= MAX_SECONDS_IN_DAY;
            }
            std::swap(m_timeSeconds, additionSeconds);
        }
        return *this;
    }
    
    // todo: -=
    // todo: *=
    // todo: /=
    
    bool operator ==(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds == tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    bool operator !=(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds != tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    bool operator >(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds > tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    bool operator <(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds < tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    bool operator >=(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds >= tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    bool operator <=(CTime const & other)const
    {
        CTime tmpCopy(other);
        if (m_timeSeconds <= tmpCopy.m_timeSeconds)
        {
            return true;
        }
        return false;
    }
    
    CTime const operator *(unsigned number)const
    {
        unsigned multiplicationResult = m_timeSeconds * number;
        return CTime((multiplicationResult > MAX_SECONDS_IN_DAY) ? multiplicationResult - MAX_SECONDS_IN_DAY : multiplicationResult);
    }
    
    // todo: number * CTime
    
    
    CTime const operator /(unsigned number)const
    {
        unsigned divisionResult = m_timeSeconds / number;
        return divisionResult;
    }
    
    unsigned operator /(CTime const & other)const
    {
        CTime tmpCopy(other);
        unsigned divisionResult = m_timeSeconds / tmpCopy.m_timeSeconds;
        return divisionResult;
    }
    
private:
    bool m_validTime;
};
