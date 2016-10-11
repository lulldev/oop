#include <iostream>
#include <map>

#include "wordFrequency.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    WordsFrequencyMap frequencyMap;
    char ch = NULL;
    string word = "";
    int wordCnt;
    
    cout << "Введите слова для подсчета встречаемости:";
    while (ch != EOF)
    {
        ch = cin.get();
        if (word != "" && (ch == '\n' || ch == ' ' || ch == '\t'))
        {
            if (frequencyWordInMap(frequencyMap, word) == 0)
            {
                frequencyMap.insert(pair <string, int> (word, 1));
            }
            else
            {
                wordCnt = frequencyMap[word];
                frequencyMap[word] = ++wordCnt;
            }
            word = "";
        }
        else
        {
            word += ch;
        }
    }
    
    cout << "Результат поиска частоты встречаемости:" << endl;
    showResult(frequencyMap);
    
    return 0;
}
