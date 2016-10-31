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
    
    return Protocol::Undifened;
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
    // regexr (http|https|ftp):\/\/([^\/:]+)+(:[0-9]+)?(\/[^\/]+)*\/?$
    regex urlRegexRule("(http|https|ftp)://([^/:]+)+(:[0-9]+)?(\/[^]+)*/?$");
    smatch urlRegexResult;
    
    if (regex_match(url, urlRegexResult, urlRegexRule))
    {
        size_t componentCounter = 0;
        string portStr, protocolStr;

        for (const auto & urlComponent : urlRegexResult)
        {
            switch(componentCounter)
            {
                case 1: // http
                    protocolStr = urlComponent;
                    transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);
                    protocol = GetProtocolByStr(protocolStr);
                    break;
                case 2: // domain
                    host = urlComponent;
                    break;
                case 3: // port
                    portStr = urlComponent;
                    if (portStr.size() > 0)
                    {
                        portStr.erase(portStr.begin());
                        port = stoi(portStr);
                    }
                    else
                    {
                        port = GetPortByProtocol(protocol);
                    }
                    break;
                case 4: // document
                    document = urlComponent;
                    break;
            }
            componentCounter++;
        }
        return true;
    }
    
    return false;
}
