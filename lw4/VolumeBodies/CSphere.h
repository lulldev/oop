#pragma once

#include "CBody.h"

class CSphere : public CBody
{
public:
    CSphere(double density, double radius);

    double GetRadius()const;
    double GetVolume() override;

private:
    double m_radius;

protected:
    void AppendCustomProperties(std::ostream & s)const override;
};