#include <iostream>
#include <string>
#include <set>
#include <cassert>

bool IsStrInStringSet(const std::string& str, const std::set<std::string>& setStringList);
bool IsWordBad(std::string& word);
bool IsCharasterIsSeparator(std::string& charaster);
void BadWordsFileFilter(std::istream& input, std::ostream& output);
void ReplaceBadWordsInLine(std::string& fileLine);