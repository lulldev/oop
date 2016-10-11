#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE word_frequency_test

#include <boost/test/unit_test.hpp>

#include "wordFrequency.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(frequency_lowercase_words)
{
    WordsFrequencyMap frequencyMap;
    
    string testString1 = "word";
    string testString2 = "hello";

    frequencyMap.insert(pair <string, int> (testString1, 3));
    frequencyMap.insert(pair <string, int> (testString2, 5));

    BOOST_CHECK(frequencyWordInMap(frequencyMap, testString1) > 0);
    BOOST_CHECK(frequencyWordInMap(frequencyMap, testString1) == 3);
    BOOST_CHECK(frequencyWordInMap(frequencyMap, testString2) == 5);

}

BOOST_AUTO_TEST_CASE(frequency_multicase_words)
{
    WordsFrequencyMap frequencyMap;
    
    string testString1 = "hello";
    string testString2 = "Hello";
    
    frequencyMap.insert(pair <string, int> (testString1, 10));
    
    BOOST_CHECK(frequencyWordInMap(frequencyMap, testString1) == 10);
    BOOST_CHECK(frequencyWordInMap(frequencyMap, testString2) == 10);
}
