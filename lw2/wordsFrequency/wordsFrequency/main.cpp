#include <iostream>
#include <map>
#include <sstream>

#include "wordFrequency.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    WordsFrequencyMap frequencyMap;
    frequencyMap = ReadWordsAndSearchFrequency(cin, cout);
    
    cout << "Результат поиска частоты встречаемости:" << endl;
    ShowResult(frequencyMap);
    
    return 0;
}
