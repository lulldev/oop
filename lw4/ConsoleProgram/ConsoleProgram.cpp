#include "ConsoleProgram.h"

using namespace std;

ConsoleProgram::ConsoleProgram(istream& input, ostream& output, vector<shared_ptr<CBody>>& bodiesArray)
    : m_input(input),
      m_output(output),
      m_bodiesArray(bodiesArray)
{
}

void ConsoleProgram::ShowHelpUsage()const
{
     m_output << "Input information about volume bodies in array\n"
         << "* For example: \n"
         << "sphere <density> <radius>\n"
         << "cone <density> <radius> <height>\n"
         << "parallelepiped <density> <width> <height> <depth>\n"
         << "cylinder <density> <radius> <height>\n"
         << "compound\n"
         << "--------------------------\n" << endl;
}

void ConsoleProgram::ProcessInputCommand(std::string inputCommand)
{
    vector<string> splitCommand { split(inputCommand, ' ') };

    try
    {
        CallCommand(splitCommand);
    }
    catch (const invalid_argument& e)
    {
        throw;
    }

}

void ConsoleProgram::CreateSphere(std::vector<std::string> const& parameters)
{
    if (parameters.size() != 3)
    {
        throw invalid_argument("Invalid count parameters");
    }

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

void ConsoleProgram::CreateParallelepiped(std::vector<std::string> const& parameters)
{

    if (parameters.size() != 5)
    {
        throw invalid_argument("Invalid count parameters");
    }

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
    catch(exception const&)
    {
        throw invalid_argument("Parallelepiped invalid parameters");
    }

    shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, width, height, depth);
    m_bodiesArray.push_back(parallelepiped);
}

void ConsoleProgram::CreateCone(std::vector<std::string> const& parameters)
{
    if (parameters.size() != 4)
    {
        throw invalid_argument("Invalid count parameters");
    }

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

void ConsoleProgram::CreateCylinder(std::vector<std::string> const& parameters)
{
    if (parameters.size() != 4)
    {
        throw invalid_argument("Invalid count parameters");
    }

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

void ConsoleProgram::CreateCompound()
{
    std::vector<shared_ptr<CBody>> compoundBodies;
    ConsoleProgram fillCompoundProgram(cin, cout, compoundBodies);
    string inputString("");

    m_output << "Input compound childs (for exit input 'save')" << endl;
    while(getline(cin, inputString) && inputString != "save")
    {
        try
        {
            fillCompoundProgram.ProcessInputCommand(inputString);
        }
        catch (const invalid_argument& e)
        {
            m_output << e.what() << endl;
        }
    }

    shared_ptr<CCompound> compound = make_shared<CCompound>();
    for (auto compoundChild : compoundBodies)
    {
        compound->AddChildBody(compoundChild);
    }

    m_bodiesArray.push_back(compound);

    m_output << "Compound input complete!" << endl;
    ShowHelpUsage();

}

void ConsoleProgram::CallCommand(std::vector<std::string>& splitCommand)
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
    else if (splitCommand[0] == TYPENAME_COMPOUND)
    {
        CreateCompound();
    }
    else
    {
        throw invalid_argument("Unknow command");
    }
}

double GetWeightInWaterByBodyDensityAndVolume(double density, double volume)
{
    const unsigned WATER_DENSITY = 1000;
    const float GRAVITY = 9.8;
    return (density - WATER_DENSITY) * GRAVITY * volume;
}

std::shared_ptr<CBody> ConsoleProgram::GetMaxMassBody()const
{
    if (m_bodiesArray.empty())
    {
        throw std::invalid_argument("Body array is empty");
    }

    auto maxBodyByMass = std::max_element(m_bodiesArray.begin(), m_bodiesArray.end(),
                                 [](std::shared_ptr<CBody>& body1, std::shared_ptr<CBody>& body2)
                                 {
                                     return body1->GetMass() < body2->GetMass();
                                 });
    return *maxBodyByMass;
}

std::shared_ptr<CBody> ConsoleProgram::GetMinWeightBody()const
{
    if (m_bodiesArray.empty())
    {
        throw std::invalid_argument("Body array is empty");
    }

    auto minBodyByWeight = std::min_element(m_bodiesArray.begin(), m_bodiesArray.end(),
                                           [](std::shared_ptr<CBody>& body1, std::shared_ptr<CBody>& body2)
                                           {
                                               double weightBody1 = GetWeightInWaterByBodyDensityAndVolume(
                                                       body1->GetDensity(), body1->GetVolume());
                                               double weightBody2 = GetWeightInWaterByBodyDensityAndVolume(
                                                       body2->GetDensity(), body2->GetVolume());
                                               return weightBody1 < weightBody2;
                                           });
    return *minBodyByWeight;

}


void ConsoleProgram::PrintVolumeBodies()const
{
    if (m_bodiesArray.empty())
    {
        m_output << "Volume bodies array is empty!" << endl;
    }

    m_output << "All bodies in program array (" << m_bodiesArray.size() << ")" << endl;

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