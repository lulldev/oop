#include <iostream>
#include <cmath>

#include "CBody.h"

using namespace std;

CBody::CBody(const std::string& type)
        : m_type(type),
          m_density(0.0)
{
}

CBody::CBody(const std::string& figureType, double density)
        : m_type(figureType)
{
    if (density < 0)
    {
        throw invalid_argument("Density must be > 0");
    }

    m_density = density;
}

double CBody::GetDensity()
{
    return RoundedByDecimals(m_density, 2);
}

double CBody::GetVolume()
{
    return RoundedByDecimals(m_volume, 2);
}

double CBody::GetMass()
{
    return GetDensity() * GetVolume();
}

string CBody::ToString()
{
    return "Type: " + m_type + "\n" +
           "Density: " + to_string(GetDensity()) + "\n" +
           "Volume: " + to_string(GetVolume()) + "\n" +
           "Mass: " + to_string(GetMass());
}

std::string CBody::GetType()const
{
    return m_type;
}
