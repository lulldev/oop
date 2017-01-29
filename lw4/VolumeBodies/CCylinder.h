#pragma once

#include "CBody.h"

class CCylinder : public CBody
{
public:
    CCylinder(double density, double radius, double height);

    double GetVolume() override;
    double GetHeight()const;
    double GetBaseRadius()const;

    std::string ToString()override;

private:
    double m_radius;
    double m_height;
};