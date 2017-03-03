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
    return m_density;
}

double CBody::GetVolume()
{
    return m_volume;
}

double CBody::GetMass()
{
    return GetDensity() * GetVolume();
}

void CBody::AppendCustomProperties(ostream & s)const
{
    (void)&s;
}

string CBody::ToString()
{
    ostringstream s;

    s << fixed << showpoint;
    s << setprecision(2);

    s << "Type: " << m_type << endl;
    s << "Density: " << GetDensity() << endl;
    s << "Volume: " << GetVolume() << endl;
    s << "Mass: " << GetMass() << endl;

    AppendCustomProperties(s);

    return s.str();
}

std::string CBody::GetType()const
{
    return m_type;
}
