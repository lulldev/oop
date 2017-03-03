#include <iostream>
#include <vector>
#include <regex>
#include <string>

#include "../VolumeBodies/VolumeBodies.h"

class ConsoleProgram
{
public:

    ConsoleProgram(std::istream& input, std::ostream& output, std::vector<std::shared_ptr<CBody>>& bodiesArray);

    void ProcessInputCommand(std::string inputCommand);
    void PrintVolumeBodies()const;
    void PrintMaxMassBody();
    void PrintMinWeightBody();
    void ShowHelpUsage()const;

    std::shared_ptr<CBody> GetMaxMassBody()const;
    std::shared_ptr<CBody> GetMinWeightBody()const;

private:
    std::vector<std::shared_ptr<CBody>>& m_bodiesArray;
    std::istream& m_input;
    std::ostream& m_output;

    void CreateSphere(std::vector<std::string>& parameters);
    void CreateParallelepiped(std::vector<std::string>& parameters);
    void CreateCone(std::vector<std::string>& parameters);
    void CreateCylinder(std::vector<std::string>& parameters);
    void CreateCompound();

    void CallCommand(std::vector<std::string>& splitCommand);
};