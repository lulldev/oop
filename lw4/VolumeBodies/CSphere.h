#pragma once

#include "CBody.h"

class CSphere : public CBody
{
public:
    CSphere(double density, double radius);

    double GetRadius()const;
    double GetVolume()const override;

    std::string ToString()const override;

private:
    double m_radius;
};