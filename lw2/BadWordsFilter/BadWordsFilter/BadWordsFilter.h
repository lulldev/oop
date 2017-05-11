#include <iostream>
#include <string>
#include <set>
#include <cassert>

bool IsStrInStringSet(const std::string& str, const std::set<std::string>& setStringList);
void BadWordsFileFilter(std::istream& input, std::ostream& output);
void ReplaceBadWordsInLine(std::string& fileLine);