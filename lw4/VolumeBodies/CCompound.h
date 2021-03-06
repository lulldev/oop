#pragma once

#include <iostream>
#include <vector>

#include "VolumeBodies.h"
#include "CBody.h"

class CCompound : public CBody
{
public:
    CCompound();

    bool AddChildBody(std::shared_ptr<CBody> const& childBody);
    double GetMass() override;
    double GetVolume() override;

private:
    std::vector<std::shared_ptr<CBody>> m_childBodies;
    bool IsValidBody(std::shared_ptr<CBody> const& childBody)const;
    void SetCompoundDensity();

protected:
    void ConcreteBodyToString(std::ostream &output)const override;
};