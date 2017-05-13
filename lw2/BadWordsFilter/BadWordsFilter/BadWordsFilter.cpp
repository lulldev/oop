#include "BadWordsFilter.h"

using namespace std;

static set<string> BAD_WORDS_LIST =  {"идиот", "дурак", "fuck", "idiot"};
static set<string> WORDS_SEPARATORS =  {" ", ".", ",", ";", ":", "?", "!"};

/**
 * @deprecated
bool IsStrInStringSet(const string& str, const set<string>& setStringList)
{
    for (auto it = begin(setStringList); it != end(setStringList); ++it)
    {
        if (str == *it)
        {
            return true;
        }
    }
    return false;
}
 */

void ReplaceBadWordsInLine(string& fileLine)
{
    string word;
    string currentChar;
    string resultLine;
    for (size_t i = 0; i <= fileLine.size(); i++)
    {
        currentChar = fileLine[i];
        word += currentChar;
        auto resultFindCharInSeparators = WORDS_SEPARATORS.find(currentChar);
        if ((resultFindCharInSeparators != WORDS_SEPARATORS.end() || (i + 1 == fileLine.size())) && word.size() != 0)
        {
            string cleanedWord = word;
            if ((i + 1 != fileLine.size()))
            {
                cleanedWord.pop_back();
            }

            auto resultFindWordInBadwordList = BAD_WORDS_LIST.find(cleanedWord);
            if(resultFindWordInBadwordList == BAD_WORDS_LIST.end())
            {
                resultLine += word;
            }

            word.erase();
        }
    }
    fileLine = resultLine;
}

/*
void ReplaceBadWordsInLine(string& fileLine)
{
    for(auto const badWord : BAD_WORDS_LIST) {
        std::replace_if(fileLine.begin(), fileLine.end(),
                        [&](auto const badWord) {
                            auto resultFindWordInBadwordList = BAD_WORDS_LIST.find(badWord);
                            return resultFindWordInBadwordList != BAD_WORDS_LIST.end();
                        }, "");
    }
}
*/

void BadWordsFileFilter(istream& input, ostream& output)
{
    string fileLine;
    while (getline(input, fileLine))
    {
        ReplaceBadWordsInLine(fileLine);
        output << fileLine << endl;
    }
}