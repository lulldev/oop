#include <vector>
#include <string>
#include <iostream>

#include "../VolumeBodies/CSphere.h"
#include "../VolumeBodies/CCone.h"
#include "../VolumeBodies/CParallelepiped.h"
#include "../VolumeBodies/CCylinder.h"

class ConsoleProgram
{
public:

    ConsoleProgram(std::istream& input, std::ostream& output, std::vector<std::shared_ptr<CBody>>& bodiesArray);

    void ProcessInputCommand(std::string inputCommand);
    bool CallCommand(std::vector<std::string> splitCommand);
    void PrintVolumeBodies()const;
    void PrintMaxMassBody();
    void PrintMinWeightBody();

private:
    std::vector<std::shared_ptr<CBody>>& m_bodiesArray;
    std::istream& m_input;
    std::ostream& m_output;

    void CreateSphere(std::vector<std::string> parameters);
    void CreateParallelepiped(std::vector<std::string> parameters);
    void CreateCone(std::vector<std::string> parameters);
    void CreateCylinder(std::vector<std::string> parameters);
};