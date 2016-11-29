// моделирует время суток, задаваемое количеством часов (0-23), минут (0-59) и
// секунд (0-59)
class CTime
{
public:
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

private:
    unsigned m_timeSeconds;
    bool m_validTime;
};
