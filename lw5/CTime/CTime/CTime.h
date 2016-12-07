#include <iostream>
#include <cmath>
#include <vector>

#include <boost/algorithm/string.hpp>

#define MAX_SECONDS_IN_DAY 86400

class CTime
{
public:
    CTime(unsigned timeStamp = 0);
    CTime(unsigned hours, unsigned minutes, unsigned seconds = 0);
    
    unsigned GetHours()const;
    unsigned GetMinutes()const;
    unsigned GetSeconds()const;
    bool IsValid()const;
    std::string FormatTime()const;
    
public:
    CTime operator +(CTime const & time2);
    CTime operator -(CTime const & time2);
    CTime & operator++();
    CTime & operator--();
    CTime const operator++(int);
    CTime const operator--(int);
    CTime & operator =(CTime const & other);
    CTime & operator +=(CTime const & other);
    CTime & operator -=(CTime const & other);
    CTime & operator *=(CTime const & other);
    CTime & operator /=(CTime const & other);
    bool operator ==(CTime const & other)const;
    bool operator !=(CTime const & other)const;
    bool operator >(CTime const & other)const;
    bool operator <(CTime const & other)const;
    bool operator >=(CTime const & other)const;
    bool operator <=(CTime const & other)const;
    CTime const operator *(unsigned number)const;
    CTime const operator /(unsigned number)const;
    unsigned operator /(CTime const & other)const;
//    std::ostream & operator<<(std::ostream & output, const СTime & time);
//    std::istream & operator>>(std::istream & input, const CTime & time);

private:
    // храним время в секундах
    unsigned m_timeSeconds;
    bool m_validTime;
    
    // считывыет из строки формата h:m:s числовое значение секунды
    unsigned ParseSecondsFromFormatTime(const std::string & formatTime)const;
};
