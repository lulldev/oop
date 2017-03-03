#include "CParallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
        :CBody(TYPENAME_PARALLELEPIPED, density)
{
    ValidateBodyArguments(width, height, depth);
    m_width = width;
    m_height = height;
    m_depth = depth;
}

void CParallelepiped::ValidateBodyArguments(double width, double height, double depth)const
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

double CParallelepiped::GetVolume()
{
    return (m_width * m_height * m_depth);
}

void CParallelepiped::AppendCustomProperties(ostream& output)const
{
    output << "Width: " << GetWidth() << endl;
    output << "Height: " << GetHeight() << endl;
    output << "Depth: " << GetDepth() << endl;
}