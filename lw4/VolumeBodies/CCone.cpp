#include <math.h>
#include <iostream>

#include "CCone.h"

using namespace std;

CCone::CCone(double density, double radius, double height)
        :CBody(TYPENAME_CONE, density)
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

double CCone::GetBaseRadius()const
{
    return m_radius;
}

double CCone::GetHeight()const
{
    return m_height;
}

double CCone::GetVolume()
{
    return (m_height / 3) * (SimplePow(m_radius, 2) * M_PI);
}

void CCone::AppendCustomProperties(ostream & s)const
{
    s << "Radius: " << GetBaseRadius() << endl;
    s << "Height: " << GetHeight() << endl;
}