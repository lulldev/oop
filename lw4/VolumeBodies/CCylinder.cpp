#include "CCylinder.h"

using namespace std;

CCylinder::CCylinder(double density, double radius, double height)
        :CBody(TYPENAME_CYLINDER, density)
{
    if (radius < 0)
    {
        throw invalid_argument("Radius must be > 0\n");
    }
    else if (height < 0)
    {
        throw invalid_argument("Height must be > 0\n");
    }

    m_radius = radius;
    m_height = height;
}

double CCylinder::GetBaseRadius()const
{
    return m_radius;
}

double CCylinder::GetHeight()const
{
    return m_height;
}

double CCylinder::GetVolume()
{
    return M_PI * SimplePow(m_radius, 3) * m_height;
}

void CCylinder::AppendCustomProperties(ostream & s)const
{
    s << "Radius: " << GetBaseRadius() << endl;
}