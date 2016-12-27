#include <iostream>
#include <regex>

#include "CHttpUrl.hpp"
#include "CUrlParsingError.hpp"

using namespace std;

CHttpUrl::CHttpUrl() {}

CHttpUrl::CHttpUrl(std::string const& url)
{
    ParseURL(url);
    m_Url = url;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned port)
    : m_Domain(domain)
    , m_Document(document)
    , m_Protocol(protocol)
    , m_Port(port)
{
    
    if (m_Port == 0)
    {
        m_Port = GetPortByProtocol(m_Protocol);
    }
    
    ValidateURLParams(m_Domain, m_Document, m_Protocol, to_string(m_Port));

    m_Url = MakeURLFromParams();
}

std::string CHttpUrl::GetProtocolName()const
{
    switch(m_Protocol)
    {
        case Protocol::HTTP:
            return "http";
            break;
        case Protocol::HTTPS:
            return "https";
            break;
        default:
            return "";
    }
    
    return "";
}

std::string CHttpUrl::ProtocolToString()const
{
    return GetProtocolName() + "://";
}

Protocol CHttpUrl::GetProtocolByStr(std::string const& strProtocol)const
{
    if (strProtocol == "http")
    {
        return Protocol::HTTP;
    }
    else if (strProtocol == "https")
    {
        return Protocol::HTTPS;
    }
    
    return Protocol::UNKNOW;
}

signed CHttpUrl::GetPortByProtocol(Protocol& protocol)const
{
    switch(protocol)
    {
        case Protocol::HTTP:
            return 80;
            break;
        case Protocol::HTTPS:
            return 443;
            break;
        default:
            return -1;
    }
    
    return -1;
}

void CHttpUrl::ValidateProtocolByStr(std::string protocol)const
{
    transform(protocol.begin(), protocol.end(), protocol.begin(), ::tolower);
    Protocol protocolEnum = GetProtocolByStr(protocol);
    
    ValidateProtocol(protocolEnum);
}

void CHttpUrl::ValidateProtocol(Protocol & protocol)const
{
    if (protocol != Protocol::HTTP && protocol != Protocol::HTTPS)
    {
        throw ErrorInvalidProtocol("Error set protocol");
    }
}

void CHttpUrl::ValidateDomain(std::string domainStr)const
{
    regex urlRegexRule("^([a-zA-Z0-9]([a-zA-Z0-9./-]{0,63}[a-zA-Z0-9])$)", regex_constants::icase);
    smatch urlRegexResult;
    
    if (!regex_match(domainStr, urlRegexResult, urlRegexRule))
    {
        throw ErrorInvalidDomain("Error set domain");
    }
}

void CHttpUrl::ValidatePort(std::string port)const
{
    signed portNumber;
    try
    {
        portNumber = stoi(port);
        if (to_string(portNumber) != port)
        {
            throw ErrorInvalidPort("Port must be number");
        }
    }
    catch(...)
    {
        throw ErrorInvalidPort("Port must be number");
    }
    
    if (portNumber < 1 || portNumber > 65536)
    {
        throw ErrorInvalidPort("Port must be 1-65536");
    }
}

void CHttpUrl::ValidateURLParams(std::string & domain, std::string & document, Protocol & protocol, std::string port)
{
    ValidateProtocol(protocol);
    ValidateDomain(domain);
    ValidatePort(port);
}

std::string CHttpUrl::MakeURLFromParams()const
{
    return ProtocolToString() + m_Domain +  to_string(m_Port) + m_Document;
}

void CHttpUrl::ParseURL(string const& url)
{
    regex urlRegexRule("([a-zA-Z0-9]+)://([^/:]+)+((?=:):([a-zA-Z0-9]+))?(/[^]+)*/?$", regex_constants::icase);
    
    smatch urlRegexResult;
    size_t componentCounter = 0;
    
    regex_match(url, urlRegexResult, urlRegexRule);
    
    for (const auto& urlComponent : urlRegexResult)
    {
        switch (componentCounter)
        {
            case 1: // http
            {
                ValidateProtocolByStr(urlComponent);
                m_Protocol = GetProtocolByStr(urlComponent);
            }
                break;
            case 2: // domain
                ValidateDomain(urlComponent);
                m_Domain = urlComponent;
                break;
            case 4: // port
            {
                string portStr = urlComponent;
                
                if (portStr.size() > 0)
                {
                    ValidatePort(portStr);
                    m_Port = stoi(portStr);
                }
                else
                {
                    m_Port = GetPortByProtocol(m_Protocol);
                }

            }
                break;
            case 5: // document
                m_Document = urlComponent;
                break;
        }
        ++componentCounter;
    }
    
    if (!regex_match(url, urlRegexResult, urlRegexRule))
    {
        throw CUrlParsingError("Wrong init url");
    }
    
}


string CHttpUrl::GetURL()const
{
    return m_Url;
}

string CHttpUrl::GetDomain()const
{
    return m_Domain;
}

string CHttpUrl::GetDocument()const
{
    return m_Document;
}

Protocol CHttpUrl::GetProtocol()const
{
    return m_Protocol;
}

unsigned short CHttpUrl::GetPort()const
{
    return m_Port;
}
