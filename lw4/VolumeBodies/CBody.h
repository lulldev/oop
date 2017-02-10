#pragma once

#include "FigureTypes.h"
#include "Helpers.h"

class CBody
{
public:

    CBody(const std::string& figureType);
    CBody(const std::string& figureType, double density);

    virtual double GetDensity();
    virtual double GetVolume();
    virtual double GetMass();

    virtual std::string ToString() final;

    std::string GetType()const;

protected:
    std::string m_type;
    double m_density;
    double m_volume;

    virtual void AppendCustomProperties(std::ostream & s)const;
};