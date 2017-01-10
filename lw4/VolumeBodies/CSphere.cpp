#include <math.h>
#include <iostream>

#include "CSphere.h"

using namespace std;

CSphere::CSphere(double density, double radius)
        : CBody(TYPENAME_SPHERE, density)
{
    if (radius < 0)
    {
        throw invalid_argument("Radius must be > 0");
    }

    m_radius = radius;
}

double CSphere::GetRadius()const
{
    return m_radius;
}

double CSphere::GetVolume()const
{
    return (4/3) * 3.14 * pow(GetRadius(), 3);
}

string CSphere::ToString()const
{
    return CBody::ToString() + "\n" +
           "Radius: " + to_string(GetRadius()) + "\n";
}