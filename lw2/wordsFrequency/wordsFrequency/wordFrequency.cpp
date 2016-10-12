#include <iostream>
#include "wordFrequency.hpp"

using namespace std;

WordsFrequencyMap ReadWordsAndSearchFrequency(std::istream & input, std::ostream & output)
{
    WordsFrequencyMap frequencyMap;
    string word;
    
    output << "Введите слова для подсчета встречаемости:";
    while (input >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        ++frequencyMap[word];
    }
    
    return frequencyMap;
}

void ShowResult(WordsFrequencyMap & frequencyMap)
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
