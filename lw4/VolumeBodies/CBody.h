#pragma once

#include "FigureTypes.h"

class CBody
{
public:

    CBody(const std::string& figureType);
    CBody(const std::string& figureType, double density);

    virtual double GetDensity();
    virtual double GetVolume()const;
    virtual double GetMass();

    virtual std::string ToString();

    std::string GetType()const;

protected:
    std::string m_type;
    double m_density;
    double m_volume;
};