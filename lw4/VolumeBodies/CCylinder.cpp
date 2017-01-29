#include <math.h>
#include <iostream>

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
    return M_PI * pow(m_radius, 3) * m_height;
}

string CCylinder::ToString()
{
    return CBody::ToString() + "\n" +
           "Radius: " + to_string(GetBaseRadius()) + "\n";
}