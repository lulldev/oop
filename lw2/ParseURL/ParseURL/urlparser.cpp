#include <string>
#include <iostream>

#include "urlparser.hpp"

using namespace std;

// TODO:
//int getURLPortByProtocol(Protocol & protocol)
//{
//    return 0;
//}

bool ParseURL(string const & url, Protocol & protocol, int & port, string & host, string & document)
{
    regex urlRegexRule("(http|https|ftp):\/\/([^/:]+):?([^\/]*)?([\/])?([^]*)?");
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
                    
                    if (protocolStr == "http")
                    {
                        protocol = Protocol::HTTP;
                    }
                    else if (protocolStr == "https")
                    {
                        protocol = Protocol::HTTPS;
                    }
                    else if (protocolStr == "ftp")
                    {
                        protocol = Protocol::FTP;
                    }
                    break;
                case 2: // domain
                    host = urlComponent;
                    break;
                case 3: // port
                    portStr = urlComponent;
                    if (portStr.size() > 0)
                    {
                        port = stoi(portStr);
                    }
                    else
                    {
                        switch(protocol)
                        {
                            case Protocol::HTTP:
                                port = 80;
                                break;
                            case Protocol::HTTPS:
                                port = 443;
                                break;
                            case Protocol::FTP:
                                port = 21;
                                break;
                        }
                    }
                    break;
                case 5: // document
                    document = urlComponent;
                    break;
            }
            componentCounter++;
        }
        return true;
    }
    
    return false;
}
