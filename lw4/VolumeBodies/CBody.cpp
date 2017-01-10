#include <iostream>

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

double CBody::GetDensity()const
{
    return m_density;
}

double CBody::GetVolume()const
{
    return m_volume;
}

double CBody::GetMass()const
{
    return GetDensity() * GetVolume();
}

string CBody::ToString()const
{
    return "Type: " + m_type + "\n" +
           "Density: " + to_string(GetDensity()) + "\n" +
           "Volume: " + to_string(GetVolume()) + "\n" +
           "Mass: " + to_string(GetMass());
}