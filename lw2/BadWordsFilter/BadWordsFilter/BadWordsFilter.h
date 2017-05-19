#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <sstream>

std::string ReadNextWord(std::istream& input, std::ostream& output, std::string& separator);
void FilterBadWord(std::string& word);
void ReplaceBadWordsInString(const std::string& inputString, std::ostream& output);