#include <string>
#include <iostream>

#include "urlparser.hpp"

using namespace std;

Protocol GetProtocolByStr(const string strProtocol)
{
    if (strProtocol == "http")
    {
        return Protocol::HTTP;
    }
    else if (strProtocol == "https")
    {
        return Protocol::HTTPS;
    }
    else if (strProtocol == "ftp")
    {
        return Protocol::FTP;
    }
    
    return Protocol::Undefined;
}

int GetPortByProtocol(Protocol & protocol)
{
    switch(protocol)
    {
        case Protocol::HTTP:
            return 80;
            break;
        case Protocol::HTTPS:
            return 443;
            break;
        case Protocol::FTP:
            return 21;
            break;
    }
    
    return -1;
}

bool ParseURL(string const & url, Protocol & protocol, int & port, string & host, string & document)
{
    regex urlRegexRule("(http|https|ftp)://([^/:]+)+((?=:):([0-9]+))?(\/[^]+)*/?$", regex_constants::icase);
    smatch urlRegexResult;
    
    if (regex_match(url, urlRegexResult, urlRegexRule))
    {
        size_t componentCounter = 0;

        for (const auto & urlComponent : urlRegexResult)
        {
            switch(componentCounter)
            {
                case 1: // http
                {
                    string protocolStr = urlComponent;
                    transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);
                    protocol = GetProtocolByStr(protocolStr);
                }
                    break;
                case 2: // domain
                    host = urlComponent;
                    break;
                case 4: // port
                {
                    string portStr = urlComponent;
                    if (portStr.size() > 0)
                    {
                        port = stoi(portStr);
                        if (port < 1 && port > 65536)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        port = GetPortByProtocol(protocol);
                    }
                }
                    break;
                case 5: // document
                    document = urlComponent;
                    break;
            }
            ++componentCounter;
        }
        return true;
    }
    
    return false;
}
