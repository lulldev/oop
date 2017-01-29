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
    // todo pow -> m_radius * m_radius
    return (m_height / 3) * (pow(m_radius, 2) * M_PI);
}

string CCone::ToString()
{
    return CBody::ToString() + "\n" +
           "Radius: " + to_string(GetBaseRadius()) + "\n" +
           "Height: " + to_string(GetHeight()) + "\n";
}