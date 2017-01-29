#pragma once

#include "CBody.h"

class CCone : public CBody
{
public:
    CCone(double density, double radius, double height);

    double GetVolume()const override;
    double GetHeight()const;
    double GetBaseRadius()const;

    std::string ToString() override;

private:
    double m_radius;
    double m_height;
};