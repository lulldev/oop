#include <map>

typedef std::map <std::string, int> WordsFrequencyMap;


bool issetWordInMap(WordsFrequencyMap & frequencyMap, std::string & needleWord);
void showResult(WordsFrequencyMap & frequencyMap);
