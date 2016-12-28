#include <iostream>

#define ERROR_MESSAGE_INVALID_URL       "Error init URL"
#define ERROR_MESSAGE_INVALID_PROTOCOL  "Error set protocol"
#define ERROR_MESSAGE_INVALID_DOMAIN    "Error set domain"
#define ERROR_MESSAGE_INVALID_PORT      "Error set port"


class CUrlParsingError : public std::invalid_argument
{
public:
    
    CUrlParsingError(std::string const& message);
    std::string GetMessage()const;
    virtual void PrintInfo()const;
    virtual ~CUrlParsingError() = default;

protected:
    std::string m_message;
};
