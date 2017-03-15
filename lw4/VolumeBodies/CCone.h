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

    void ValidateBodyArguments(double radius, double height)const;


protected:
    void ConcreteBodyToString(std::ostream &output)const override;
};