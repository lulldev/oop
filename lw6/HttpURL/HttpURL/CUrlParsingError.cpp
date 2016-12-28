#include <iostream>

#include "CUrlParsingError.hpp"

using namespace std;

CUrlParsingError::CUrlParsingError(std::string const& message)
    : std::invalid_argument(message)
{
    m_message = what();
}

string CUrlParsingError::GetMessage()const
{
    return m_message;
}

void CUrlParsingError::PrintInfo()const
{
    std::cout << "UrlParsingError exception: " << m_message << "\n";
}
