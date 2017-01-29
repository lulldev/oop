#include <iostream>
#include <vector>

#include "VolumeBodies.h"

using namespace std;

CCompound::CCompound(std::vector<std::shared_ptr<CBody>>& childBodiesArray)
        : CBody(TYPENAME_COMPOUND),
          m_childBodies(childBodiesArray)
{
}

bool CCompound::IsValidBody(const CBody& body)const
{
    return body.GetType() == TYPENAME_SPHERE ||
           body.GetType() == TYPENAME_CONE ||
           body.GetType() == TYPENAME_PARALLELEPIPED ||
           body.GetType() == TYPENAME_CYLINDER ||
           body.GetType() == TYPENAME_COMPOUND;
}

bool CCompound::AddChildBody(CBody& chldBody)
{
    // todo: проверка на родительские
    if (std::addressof(chldBody) == this)
    {
        throw invalid_argument("Assign yourself body error");
    }

    if (IsValidBody(chldBody))
    {
        cout << "add";
        m_childBodies.push_back(make_shared<CBody>(chldBody));
        return true;
    }

    return false;
}

double CCompound::GetMass()
{
    double mass = 0.0;

    if (!m_childBodies.empty())
    {
        for (auto childBody : m_childBodies)
        {
            cout << childBody->GetType() << "|" << childBody->GetMass() << endl;
            //mass += childBody->GetMass();
        }
    }
    //cout << mass;
    return mass;
}


double CCompound::GetVolume()
{
    double volume = 0.0;

    if (!m_childBodies.empty())
    {
        for (auto childBody : m_childBodies)
        {
            volume += childBody->GetVolume();
        }
    }

    return volume;
}


double CCompound::GetDensity()
{
    return GetMass() / GetVolume();
}
