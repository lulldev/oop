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

double CSphere::GetVolume()
{
    return (4/3) * 3.14 * SimplePow(GetRadius(), 3);
}

void CSphere::AppendCustomProperties(ostream & s)const
{
    s << "Radius: " << GetRadius() << endl;
}
