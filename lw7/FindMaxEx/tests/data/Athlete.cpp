#include "Athlete.h"

CAthlete::CAthlete() = default;

CAthlete::CAthlete()
        : CAthlete(std::string(""), 0, 0)
{
}

CAthlete::CAthlete(const std::string& fullName, double height, double weight)
    : m_fullname(fullName)
    , m_height(height)
    , m_weight(weight)
{
}

std::string CAthlete::GetFullname()const
{
    return m_fullname;
}

double CAthlete::GetHeight()const
{
    return m_height;
}

double CAthlete::GetWeight()const
{
    return m_weight;
}