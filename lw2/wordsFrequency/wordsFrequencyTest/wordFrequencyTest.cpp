#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE word_frequency_test

#include <boost/test/unit_test.hpp>

#include "wordFrequency.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(frequency_multi_words)
{
    WordsFrequencyMap frequencyMap, frequencyMapTest;
    
    string testString1 = "word";
    string testString2 = "hello";

    frequencyMapTest.insert(pair <string, size_t> (testString1, 2u));
    frequencyMapTest.insert(pair <string, size_t> (testString2, 3u));
    
    std::istringstream isstr("Hello hello heLLo Word WORD");
    std::ostringstream osstr;
    frequencyMap = ReadWordsAndSearchFrequency(isstr, osstr);
    BOOST_CHECK(frequencyMap == frequencyMapTest);
}

