#include <string>
#include <vector>

class CAthlete
{
public:
    CAthlete();
    CAthlete(const std::string& fullName, double height, double weight);

    std::string GetFullname()const;
    double GetHeight()const;
    double GetWeight()const;

private:
    std::string m_fullname;
    double m_height;
    double m_weight;
};
