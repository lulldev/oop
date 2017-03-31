#include <iostream>
#include <vector>

class CAthlete
{
public:
    CAthlete();
    CAthlete(std::string fullName, double height, double weight);

    std::string GetFullname()const;
    double GetHeight()const;
    double GetWeight()const;

//    bool operator < (const CAthlete& athlete1, const CAthlete& athlete2);
private:
    std::string m_fullname;
    double m_height;
    double m_weight;
};
