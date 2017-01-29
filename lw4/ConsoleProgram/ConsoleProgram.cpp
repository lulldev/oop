#include <iostream>
#include <vector>
#include <regex>
#include <string>

#include "ConsoleProgram.h"

using namespace std;

const vector<string> split(const string& targetString, const char& delimiter)
{
    string tmpString("");
    vector<string> resultStringVector;

    for(auto prepareString : targetString)
    {
        if(prepareString != delimiter)
        {
            tmpString += prepareString;
        }
        else if(prepareString == delimiter && tmpString != "")
        {
            resultStringVector.push_back(tmpString);
            tmpString = "";
        }
    }

    if(tmpString != "")
    {
        resultStringVector.push_back(tmpString);
    }

    return resultStringVector;
}

ConsoleProgram::ConsoleProgram(istream& input, ostream& output, vector<shared_ptr<CBody>>& bodiesArray)
    : m_input(input),
      m_output(output),
      m_bodiesArray(bodiesArray)
{
}

void ConsoleProgram::ProcessInputCommand(std::string inputCommand)
{
    vector<string> splitCommand{split(inputCommand, ' ')};

    if (splitCommand.size() < 2)
    {
        throw invalid_argument("Invalid number parameters");
    }
    else
    {
        if (!CallCommand(splitCommand))
        {
            throw invalid_argument("Unknow parameters");
        }
    }
}

void ConsoleProgram::CreateSphere(std::vector<std::string>& parameters)
{
    double density;
    double radius;

    try
    {
        density = stod(parameters[1]);
        radius = stod(parameters[2]);
    }
    catch(const std::exception& e)
    {
        throw invalid_argument("Sphere invalid parameters");
    }

    shared_ptr<CBody> sphere = make_shared<CSphere>(density, radius);
    m_bodiesArray.push_back(sphere);
}

void ConsoleProgram::CreateParallelepiped(std::vector<std::string>& parameters)
{
    double density;
    double width;
    double height;
    double depth;

    try
    {
        density = stod(parameters[1]);
        width = stod(parameters[2]);
        height = stod(parameters[3]);
        depth = stod(parameters[4]);
    }
    catch(invalid_argument const& e)
    {
        throw invalid_argument("Parallelepiped invalid parameters");
    }

    shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, width, height, depth);
    m_bodiesArray.push_back(parallelepiped);
}

void ConsoleProgram::CreateCone(std::vector<std::string>& parameters)
{

    double density;
    double radius;
    double height;

    try
    {
        density = stod(parameters[1]);
        radius = stod(parameters[2]);
        height = stod(parameters[3]);
    }
    catch(invalid_argument const& e)
    {
        throw invalid_argument("Cone invalid parameters");
    }

    shared_ptr<CBody> cone = make_shared<CCone>(density, radius, height);
    m_bodiesArray.push_back(cone);
}

void ConsoleProgram::CreateCylinder(std::vector<std::string>& parameters)
{
    double density;
    double radius;
    double height;

    try
    {
        density = stod(parameters[1]);
        radius = stod(parameters[2]);
        height = stod(parameters[3]);
    }
    catch(invalid_argument const& e)
    {
        throw invalid_argument("Cylinder invalid parameters");
    }

    shared_ptr<CBody> cylinder = make_shared<CCylinder>(density, radius, height);
    m_bodiesArray.push_back(cylinder);
}

bool ConsoleProgram::CallCommand(std::vector<std::string>& splitCommand)
{
    if (splitCommand[0] == TYPENAME_SPHERE)
    {
        CreateSphere(splitCommand);
    }
    else if (splitCommand[0] == TYPENAME_PARALLELEPIPED)
    {
        CreateParallelepiped(splitCommand);
    }
    else if (splitCommand[0] == TYPENAME_CONE)
    {
        CreateCone(splitCommand);
    }
    else if (splitCommand[0] == TYPENAME_CYLINDER)
    {
        CreateCylinder(splitCommand);
    }
    else
    {
        return false;
    }

    return true;
}

const double GetWeightByBodyDensityAndVolume(double density, double volume)
{
    return (density - 1000) * 9.8 * volume;
}

std::shared_ptr<CBody> ConsoleProgram::GetMaxMassBody()const
{
    if (m_bodiesArray.empty())
    {
        throw std::invalid_argument("Body array is empty");
    }

    auto maxBodyMass = m_bodiesArray.front();

    for (auto &concreteBody : m_bodiesArray)
    {
        if (concreteBody->GetMass() > maxBodyMass->GetMass())
        {
            maxBodyMass = concreteBody;
        }
    }

    return maxBodyMass;
}

std::shared_ptr<CBody> ConsoleProgram::GetMinWeightBody()const
{
    if (m_bodiesArray.empty())
    {
        throw std::invalid_argument("Body array is empty");
    }

    auto minBodyWeght = m_bodiesArray.front();

    double minWeight = GetWeightByBodyDensityAndVolume(minBodyWeght->GetDensity(), minBodyWeght->GetVolume());
    double weight;

    for (auto &concreteBody : m_bodiesArray)
    {
        weight = GetWeightByBodyDensityAndVolume(minBodyWeght->GetDensity(), minBodyWeght->GetVolume());
        if (weight < minWeight)
        {
            minBodyWeght = concreteBody;
            minWeight = weight;
        }
    }

    return minBodyWeght;
}


void ConsoleProgram::PrintVolumeBodies()const
{
    if (m_bodiesArray.empty())
    {
        m_output << "Volume bodies array is empty!" << endl;
    }

    m_output << "All bodies in program array:" << endl;

    for (auto &concreteBody : m_bodiesArray)
    {
        m_output << concreteBody->ToString() << endl;
    }
}

void ConsoleProgram::PrintMaxMassBody()
{
    m_output << "Volume body with MAX mass:" << endl;
    m_output << GetMaxMassBody()->ToString() << endl;
}


void ConsoleProgram::PrintMinWeightBody()
{
    m_output << "Volume body with MIN weight:" << endl;
    m_output << GetMinWeightBody()->ToString() << endl;
}