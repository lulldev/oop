#include <iostream>
#include "wordFrequency.h"

using namespace std;

bool icompare_util(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

bool icompare(std::string const& a, std::string const& b)
{
    if (a.length() == b.length())
    {
        return std::equal(b.begin(), b.end(), a.begin(), icompare_util);
    }
    else
    {
        return false;
    }
}

bool issetWordInMap(WordsFrequencyMap & frequencyMap, string & needleWord)
{
    if (!frequencyMap.empty())
    {
        for(auto it = frequencyMap.begin(); it != frequencyMap.end(); ++it)
        {
            if (!icompare(it->first, needleWord))
            {
                return true;
            }
        }
    }
    
    return false;
}

void showResult(WordsFrequencyMap & frequencyMap)
{
    if (!frequencyMap.empty())
    {
        for(auto it = frequencyMap.begin(); it != frequencyMap.end(); ++it)
        {
            cout << it->first << ": " << it->second << endl;
        }
    }
    else
    {
        cout << "Введенные слова не встречались!" << endl;
    }
}
