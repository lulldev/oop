#include "BadWordsFilter.h"

using namespace std;

namespace
{
    set<string> BAD_WORDS_LIST =  {"идиот", "дурак", "fuck", "idiot"};
    string WORDS_SEPARATORS = " .,;:?!\t";
}

string ReadNextWord(istream& input, ostream& output, string& separator)
{
    separator.clear();
    char currentChar;
    string word;
    while (input.get(currentChar))
    {
        if (WORDS_SEPARATORS.find(currentChar) != std::string::npos)
        {
            separator = currentChar;
            return word.empty() ? separator : word;
        }
        word += currentChar;
    }
    return word;
}

void FilterBadWord(string& word)
{
    auto resultFindWordInBadwordList = BAD_WORDS_LIST.find(word);
    if(resultFindWordInBadwordList != BAD_WORDS_LIST.end())
    {
        word.erase();
    }
}

void ReplaceBadWordsInString(const string& inputString, ostream& output)
{
    string word;
    string separator;
    istringstream input(inputString);

    while (!(word = ReadNextWord(input, output, separator)).empty())
    {
        FilterBadWord(word);
        output << word;
        if (word != separator)
        {
            output << separator;
        }
    }
}

