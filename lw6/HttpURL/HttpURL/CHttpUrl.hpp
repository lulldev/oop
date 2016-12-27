#include <iostream>

enum Protocol
{
    UNKNOW,
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    
    CHttpUrl();

    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);
    
    /* инициализирует URL на основе переданных параметров.
     При недопустимости входных параметров выбрасывает исключение
     std::invalid_argument
     Если имя документа не начинается с символа /, то добавляет / к имени документа
     */
    
    CHttpUrl(
             std::string const& domain,
             std::string const& document,
             Protocol = HTTP,
             unsigned port = 80);
    
    ~CHttpUrl() = default;

    
    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в URL не должен включаться
    std::string GetURL()const;
    
    // возвращает доменное имя
    std::string GetDomain()const;
    
    /*
     Возвращает имя документа. Примеры:
     /
     /index.html
     /images/photo.jpg
     */
    std::string GetDocument()const;
    
    // возвращает тип протокола
    Protocol GetProtocol()const;
    
    // возвращает номер порта
    unsigned short GetPort()const;

private:
    std::string m_Url;
    std::string m_Domain;
    std::string m_Document;
    Protocol m_Protocol;
    unsigned m_Port;
    
    // parsing
    void ParseURL(std::string const& url);
    Protocol GetProtocolByStr(std::string const& strProtocol)const;
    signed GetPortByProtocol(Protocol& protocol)const;
    
    // validation
    void ValidateURLParams(std::string & domain, std::string & document, Protocol & protocol, std::string port);
    void ValidateProtocol(Protocol & protocol)const;
    void ValidateProtocolByStr(std::string protocol)const;
    void ValidateDomain(std::string domain)const;
    void ValidatePort(std::string port)const;
    
    std::string GetProtocolName()const;
    std::string ProtocolToString()const;
    std::string MakeURLFromParams()const;

};
