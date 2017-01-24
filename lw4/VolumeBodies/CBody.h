#pragma once

#include "FigureTypes.h"

class CBody
{
public:

    CBody(const std::string& figureType);
    CBody(const std::string& figureType, double density);

    double GetDensity()const;
    virtual double GetVolume()const;
    virtual double GetMass()const;
    std::string GetType()const;
    virtual std::string ToString()const;

protected:
    std::string m_type;
    double m_density;
    double m_volume;
};