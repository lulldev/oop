#pragma once

#include "CBody.h"

class CParallelepiped : public CBody
{
public:
    CParallelepiped(double density, double width, double height, double depth);

    double GetWidth()const;
    double GetHeight()const;
    double GetDepth()const;
    double GetVolume()const override;

    std::string ToString() override;

private:
    double m_width;
    double m_height;
    double m_depth;
};