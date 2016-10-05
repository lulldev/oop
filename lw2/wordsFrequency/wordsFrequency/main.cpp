#include <iostream>
#include <map>

#include "wordFrequency.h"

using namespace std;

int main(int argc, const char * argv[])
{
    WordsFrequencyMap frequencyMap;
    char ch = NULL;
    string word = "";
    int wordCnt;
    
    cout << "Введите слова для подсчета встречаемости:" << endl;
    while (ch != EOF)
    {
        ch = cin.get();
        if (word != "" && (ch == '\n' || ch == ' ' || ch == '\t'))
        {
            if (!issetWordInMap(frequencyMap, word))
            {
                frequencyMap.insert(pair <string, int> (word, 1));
            }
            else
            {
                // TODO: word to small case
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
