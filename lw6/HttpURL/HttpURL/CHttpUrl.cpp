#include <iostream>
#include <regex>

#include "CHttpUrl.hpp"
#include "CUrlParsingError.hpp"

using namespace std;

CHttpUrl::CHttpUrl(std::string const& url)
{
    ParseURL(url);
    m_url = url;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned port)
    : m_domain(domain)
    , m_document(document)
    , m_protocol(protocol)
    , m_port(port)
{
    
    if (m_port == 0)
    {
        m_port = GetPortByProtocol(m_protocol);
    }
    
    ValidateURLParams(m_domain, m_document, m_protocol, to_string(m_port));

    m_url = MakeURLFromParams();
}

std::string CHttpUrl::GetProtocolName()const
{
    switch(m_protocol)
    {
        case Protocol::HTTP:
            return HTTP_PROTOCOL;
            break;
        case Protocol::HTTPS:
            return HTTPS_PROTOCOL;
            break;
        default:
            return "";
    }
    
    return "";
}

std::string CHttpUrl::ProtocolToString()const
{
    return GetProtocolName();
}

Protocol CHttpUrl::GetProtocolByStr(std::string const& strProtocol)const
{
    if (strProtocol == HTTP_PROTOCOL)
    {
        return Protocol::HTTP;
    }
    else if (strProtocol == HTTPS_PROTOCOL)
    {
        return Protocol::HTTPS;
    }
    
    return Protocol::UNKNOWN;
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
        throw CUrlParsingError(ERROR_MESSAGE_INVALID_PROTOCOL);
    }
}

void CHttpUrl::ValidateDomain(std::string domainStr)const
{
    regex urlRegexRule("^([a-zA-Z0-9]([a-zA-Z0-9./-]{0,63}[a-zA-Z0-9])$)", regex_constants::icase);
    smatch urlRegexResult;
    
    if (!regex_match(domainStr, urlRegexResult, urlRegexRule))
    {
        throw CUrlParsingError(ERROR_MESSAGE_INVALID_DOMAIN);
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
            throw CUrlParsingError(ERROR_MESSAGE_INVALID_PORT);
        }
    }
    catch(...)
    {
        throw CUrlParsingError(ERROR_MESSAGE_INVALID_PORT);
    }
    
    if (portNumber < 1 || portNumber > 65536)
    {
        throw CUrlParsingError(ERROR_MESSAGE_INVALID_PORT);
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
    return ProtocolToString() + "://" + m_domain +  to_string(m_port) + m_document;
}

void CHttpUrl::ParseURL(string const& url)
{
    regex urlRegexRule("([a-zA-Z0-9]+)://([^/:]+):?((?!:)[a-zA-Z0-9]+)?(/[^]+)*/?$", regex_constants::icase);
    smatch urlRegexResult;
    
    if (!regex_match(url, urlRegexResult, urlRegexRule))
    {
        throw CUrlParsingError(ERROR_MESSAGE_INVALID_URL);
    }
    
    ValidateProtocolByStr(urlRegexResult[1]);
    m_protocol = GetProtocolByStr(urlRegexResult[1]);
    
    ValidateDomain(urlRegexResult[2]);
    m_domain = urlRegexResult[2];
    
    string portStr = urlRegexResult[3];
    
    if (portStr.size() > 0)
    {
        ValidatePort(portStr);
        m_port = stoi(portStr);
    }
    else
    {
        m_port = GetPortByProtocol(m_protocol);
    }
    
    m_document = urlRegexResult[4];
}


string CHttpUrl::GetURL()const
{
    return m_url;
}

string CHttpUrl::GetDomain()const
{
    return m_domain;
}

string CHttpUrl::GetDocument()const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol()const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort()const
{
    return m_port;
}

std::string CHttpUrl::GetStringProtocol()const
{
    return ProtocolToString();
}

