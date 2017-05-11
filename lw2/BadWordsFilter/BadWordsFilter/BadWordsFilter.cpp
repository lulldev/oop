#include "BadWordsFilter.h"

using namespace std;

const set<string> BAD_WORDS_LIST =  {"идиот", "дурак", "fuck"};
const set<string> WORDS_SEPARATORS =  {" ", ".", ",", ";", ":", "?", "!"};

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

void ReplaceBadWordsInLine(string& fileLine)
{
    string word;
    string currentChar;
    string resultLine;
    for (size_t i = 0; i <= fileLine.size(); i++)
    {
        currentChar = fileLine[i];
        word += currentChar;
        if ((IsStrInStringSet(currentChar, WORDS_SEPARATORS) || (i + 1 == fileLine.size())) && word.size() != 0)
        {
            string cleanedWord = word;
            if ((i + 1 != fileLine.size()))
            {
                cleanedWord.pop_back();
            }

            if(!IsStrInStringSet(cleanedWord, BAD_WORDS_LIST))
            {
                resultLine += word;
            }

            word.erase();
        }
    }
    fileLine = resultLine;
}

void BadWordsFileFilter(istream& input, ostream& output)
{
    string fileLine;
    while (getline(input, fileLine))
    {
        ReplaceBadWordsInLine(fileLine);
        output << fileLine << endl;
    }
}