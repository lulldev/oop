#include <iostream>

#include "CUrlParsingError.hpp"

using namespace std;

// Base

CUrlParsingError::CUrlParsingError(std::string const& message) : std::invalid_argument(message)
{
    m_message = message;
}

string CUrlParsingError::GetMessage()const
{
    return m_message;
}

void CUrlParsingError::PrintInfo()const
{
    std::cout << "Base UrlParsingError exception: " << m_message << "\n";
}

// Invalid protocol

ErrorInvalidProtocol::ErrorInvalidProtocol(std::string const& message) : CUrlParsingError(message)
{
    m_message = message;
}

void ErrorInvalidProtocol::PrintInfo()const
{
    std::cout << "ErrorInvalidProtocol exception: " << m_message << "\n";
}

// Invalid port

ErrorInvalidPort::ErrorInvalidPort(std::string const& message) : CUrlParsingError(message)
{
    m_message = message;
}

void ErrorInvalidPort::PrintInfo()const
{
    std::cout << "ErrorInvalidPort exception: " << m_message << "\n";
}

// Invalid domain

ErrorInvalidDomain::ErrorInvalidDomain(std::string const& message) : CUrlParsingError(message)
{
    m_message = message;
}

void ErrorInvalidDomain::PrintInfo()const
{
    std::cout << "ErrorInvalidDomain exception: " << m_message << "\n";
}
