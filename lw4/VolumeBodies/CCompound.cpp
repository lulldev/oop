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
    if (std::addressof(chldBody) == this)
    {
        throw invalid_argument("Assign yourself body error");
    }

    if (IsValidBody(chldBody))
    {
        m_childBodies.push_back(make_shared<CBody>(chldBody));
        return true;
    }

    return false;
}

double CCompound::GetMass()const
{
    double mass = 0.0;

    if (!m_childBodies.empty())
    {
        for (auto childBody : m_childBodies)
        {
            mass += childBody->GetMass();
        }
    }

    return mass;
}


