#pragma once

#include <math.h>
#include <iostream>

#include "CBody.h"

class CParallelepiped : public CBody
{
public:
    CParallelepiped(double density, double width, double height, double depth);

    double GetWidth()const;
    double GetHeight()const;
    double GetDepth()const;
    double GetVolume() override;

private:
    double m_width;
    double m_height;
    double m_depth;

    void ValidateBodyArguments(double width, double height, double depth)const;

protected:
    void ConcreteBodyToString(std::ostream &output)const override;
};