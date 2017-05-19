#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>

#include "lib/catch.hpp"
#include "BadWordsFilter/BadWordsFilter.h"

using namespace std;

void ClearOstream(std::ostringstream& osstr)
{
    osstr.str("");
    osstr.clear();
    osstr.seekp(0);
}

TEST_CASE("Filter can process empty strings", "[ReplaceBadWordsInString]")
{
    std::string inputstring("");
    std::ostringstream osstr;
    ReplaceBadWordsInString(inputstring, osstr);
    REQUIRE(osstr.str() == string(""));
    ClearOstream(osstr);
}

TEST_CASE("Filter not modify string without bad words", "[ReplaceBadWordsInString]")
{
    std::string inputstring("this is line without bad words");
    std::ostringstream osstr;
    ReplaceBadWordsInString(inputstring, osstr);
    REQUIRE(osstr.str() == string("this is line without bad words"));
    ClearOstream(osstr);
}

TEST_CASE("Filter can right delete bad words", "[ReplaceBadWordsInString]")
{
    std::ostringstream osstr;
    
    SECTION("Can filter russian words") {
        std::string inputstring("привет, как дела, дурак");
        ReplaceBadWordsInString(inputstring, osstr);
        REQUIRE(osstr.str() == string("привет, как дела, "));
        ClearOstream(osstr);

        std::string inputstring2("дурак! привет, как дела");
        ReplaceBadWordsInString(inputstring2, osstr);
        REQUIRE(osstr.str() == string("! привет, как дела"));
        ClearOstream(osstr);
    }

    SECTION("Can filter english words") {
        std::string inputstring("idiot,are you hear me?");
        ReplaceBadWordsInString(inputstring, osstr);
        REQUIRE(osstr.str() == string(",are you hear me?"));
        ClearOstream(osstr);

        inputstring = "hello  man fuck";
        ReplaceBadWordsInString(inputstring, osstr);
        REQUIRE(osstr.str() == string("hello  man "));
        ClearOstream(osstr);
    }
}