#include "BadWordsFilter.h"

using namespace std;

namespace
{
    set<string> BAD_WORDS_LIST =  {"идиот", "дурак", "fuck", "idiot"};
    set<string> WORDS_SEPARATORS =  {" ", ".", ",", ";", ":", "?", "!"};
}

string ReadNextWord(istream& input, ostream& output, string& separator)
{
    char currentChar;
    string word;
    while (input.read(&currentChar, 1))
    {
        string currentCharString = string(1, currentChar);
        auto resultFindCharInSeparators = WORDS_SEPARATORS.find(currentCharString);
        if (resultFindCharInSeparators != WORDS_SEPARATORS.end())
        {
            separator = currentCharString;
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
    string separator("");
    istringstream input(inputString);

    while (!(word = ReadNextWord(input, output, separator)).empty())
    {
        FilterBadWord(word);
        output << word;
        if (word != separator)
        {
            output << separator;
        }
        separator.erase();
    }
}

