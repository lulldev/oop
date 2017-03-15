#pragma once

#include <math.h>
#include <iostream>

#include "CBody.h"

class CSphere : public CBody
{
public:
    CSphere(double density, double radius);

    double GetRadius()const;
    double GetVolume() override;

private:
    double m_radius;

    void ValidateBodyArguments(double radius)const;


protected:
    void ConcreteBodyToString(std::ostream &output)const override;
};