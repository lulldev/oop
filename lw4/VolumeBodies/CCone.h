#pragma once

#include <math.h>
#include <iostream>

#include "CBody.h"

class CCone : public CBody
{
public:
    CCone(double density, double radius, double height);

    double GetVolume() override;
    double GetHeight()const;
    double GetBaseRadius()const;

private:
    double m_radius;
    double m_height;

protected:
    void AppendCustomProperties(std::ostream & s)const override;
};