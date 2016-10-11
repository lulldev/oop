#include <iostream>
#include "wordFrequency.hpp"

using namespace std;

size_t frequencyWordInMap(WordsFrequencyMap & frequencyMap, string & needleWord)
{
    size_t frequencyCount = 0;
    if (!frequencyMap.empty())
    {
        for(auto it = frequencyMap.begin(); it != frequencyMap.end(); ++it)
        {
            transform(needleWord.begin(), needleWord.end(), needleWord.begin(), ::tolower);
            if (it->first == needleWord)
            {
                frequencyCount = it->second;
            }
        }
    }
    
    return frequencyCount;
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
