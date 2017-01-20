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
    return body.m_type == TYPENAME_SPHERE ||
           body.m_type == TYPENAME_CONE ||
           body.m_type == TYPENAME_PARALLELEPIPED ||
           body.m_type == TYPENAME_CYLINDER ||
           body.m_type == TYPENAME_COMPOUND;
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
    return 0.0;
}


