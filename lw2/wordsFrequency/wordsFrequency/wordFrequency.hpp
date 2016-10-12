#include <map>

typedef std::map <std::string, size_t> WordsFrequencyMap;

WordsFrequencyMap ReadWordsAndSearchFrequency(std::istream & input, std::ostream & output);
void ShowResult(WordsFrequencyMap & frequencyMap);
