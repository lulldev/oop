#pragma once

#include "CBody.h"

class CCylinder : public CBody
{
public:
    CCylinder(double density, double radius, double height);

    double GetVolume() override;
    double GetHeight()const;
    double GetBaseRadius()const;

private:
    double m_radius;
    double m_height;

protected:
    void AppendCustomProperties(std::ostream & s)const override;
};