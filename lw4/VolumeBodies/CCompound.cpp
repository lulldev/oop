#include "VolumeBodies.h"

using namespace std;

CCompound::CCompound():
        CBody(TYPENAME_COMPOUND)
{
}

bool CCompound::IsValidBody(std::shared_ptr<CBody> const& childBody)const
{
    return childBody->GetType() == TYPENAME_SPHERE ||
           childBody->GetType() == TYPENAME_CONE ||
           childBody->GetType() == TYPENAME_PARALLELEPIPED ||
           childBody->GetType() == TYPENAME_CYLINDER ||
           childBody->GetType() == TYPENAME_COMPOUND;
}

double CCompound::GetMass()
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

void CCompound::SetCompoundDensity()
{
    m_density = 0;

    if (GetVolume() > 0)
    {
        m_density = GetMass() / GetVolume();
    }
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> const& childBody) //(CBody& chldBody)
{
    if (childBody.get() == this)
    {
        throw invalid_argument("Assign yourself body error");
    }

    if (IsValidBody(childBody))
    {
        m_childBodies.push_back(childBody);
        SetCompoundDensity();
        return true;
    }

    return false;
}

void CCompound::ConcreteBodyToString(ostream &output)const
{
    output << "Childs (" << m_childBodies.size() << "):" << endl;

    if (m_childBodies.size() > 0)
    {
        for (auto childBody : m_childBodies)
        {
            output << childBody->ToString() << endl;
        }
    }
    else
    {
        output << "No childs" << endl;
    }
}