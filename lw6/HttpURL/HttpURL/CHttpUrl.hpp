#include <iostream>

#define HTTP_PROTOCOL  "http"
#define HTTPS_PROTOCOL "https"

enum Protocol
{
    UNKNOWN,
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
    
    std::string GetStringProtocol()const;
    
private:
    std::string m_url;
    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned m_port;
    
    // parsing
    void ParseURL(std::string const& url);
    Protocol GetProtocolByStr(std::string const& strProtocol)const;
    signed GetPortByProtocol(Protocol& protocol)const;
    Protocol GetProtocolByPort(signed port)const;
    
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
