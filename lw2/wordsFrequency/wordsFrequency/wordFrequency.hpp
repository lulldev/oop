#include <map>

typedef std::map <std::string, int> WordsFrequencyMap;

size_t frequencyWordInMap(WordsFrequencyMap & frequencyMap, std::string & needleWord);
void showResult(WordsFrequencyMap & frequencyMap);
