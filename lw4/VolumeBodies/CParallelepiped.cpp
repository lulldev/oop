#include <math.h>
#include <iostream>

#include "CParallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
        :CBody(TYPENAME_PARALLELEPIPED, density)
{
    if (width < 0)
    {
        throw std::invalid_argument("Width must be > 0\n");
    }
    else if (height < 0)
    {
        throw std::invalid_argument("Height must be > 0\n");
    }
    else if (depth < 0)
    {
        throw std::invalid_argument("Depth must be > 0\n");
    }

    m_width = width;
    m_height = height;
    m_depth = depth;
}


double CParallelepiped::GetWidth()const
{
    return m_width;
}

double CParallelepiped::GetHeight()const
{
    return m_height;
}

double CParallelepiped::GetDepth()const
{
    return m_depth;
}

double CParallelepiped::GetVolume() const
{
    return (m_width * m_height * m_depth);
}

string CParallelepiped::ToString()const
{
    return CBody::ToString() + "\n" +
           "Width: " + to_string(GetWidth()) + "\n" +
           "Height: " + to_string(GetHeight()) + "\n" +
           "Depth: " + to_string(GetDepth()) + "\n";
}