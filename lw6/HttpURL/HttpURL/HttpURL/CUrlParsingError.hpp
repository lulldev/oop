#include <iostream>

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

class ErrorInvalidProtocol : public CUrlParsingError
{
public:
    ErrorInvalidProtocol(std::string const& message);
    std::string GetMessage()const;
    virtual void PrintInfo()const;
    virtual ~ErrorInvalidProtocol() = default;
};

class ErrorInvalidPort : public CUrlParsingError
{
public:
    ErrorInvalidPort(std::string const& message);
    std::string GetMessage()const;
    virtual void PrintInfo()const;
    virtual ~ErrorInvalidPort() = default;
};

class ErrorInvalidDomain : public CUrlParsingError
{
public:
    ErrorInvalidDomain(std::string const& message);
    std::string GetMessage()const;
    virtual void PrintInfo()const;
    virtual ~ErrorInvalidDomain() = default;
};

