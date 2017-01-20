#pragma once

#include <iostream>
#include <vector>

#include "CBody.h"

class CCompound : public CBody
{
public:
    CCompound(std::vector<std::shared_ptr<CBody>>& childBodiesArray);

    bool AddChildBody(CBody& chldBody);
    double GetMass()const override;

private:
    std::vector<std::shared_ptr<CBody>> m_childBodies;
    bool IsValidBody(const CBody& body)const;
};