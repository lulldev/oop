#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>

#include "lib/catch.hpp"
#include "BadWordsFilter/BadWordsFilter.h"

using namespace std;

TEST_CASE("Filter can process empty strings", "[ReplaceBadWordsInLine]")
{
    string stringLine("");
    ReplaceBadWordsInLine(stringLine);
    REQUIRE(stringLine == string(""));
}

TEST_CASE("Filter not modify string without bad words", "[ReplaceBadWordsInLine]")
{
    string stringLine("this is line without bad words");
    ReplaceBadWordsInLine(stringLine);
    REQUIRE(stringLine == string("this is line without bad words"));
}

TEST_CASE("Filter can right delete bad words", "[ReplaceBadWordsInLine]")
{
    string stringLine;
    SECTION("Can filter russian words") {
        stringLine = "привет, как дела, дурак";
        ReplaceBadWordsInLine(stringLine);
        REQUIRE(stringLine == string("привет, как дела, "));
        stringLine = "дурак! привет, как дела";
        ReplaceBadWordsInLine(stringLine);
        REQUIRE(stringLine == string(" привет, как дела"));
    }

    SECTION("Can filter english words") {
        stringLine = "idiot,are you hear me?";
        ReplaceBadWordsInLine(stringLine);
        REQUIRE(stringLine == string("are you hear me?"));
        stringLine = "hey dude!?fuck you!";
        ReplaceBadWordsInLine(stringLine);
        REQUIRE(stringLine == string("hey dude!?you!"));
    }
}

TEST_CASE("Testing i/o stream", "[BadWordsFileFilter]")
{
    std::istringstream isstr("hey dude, this is text!\nfuck are you see that?\nэй,дурак,как дела?");
    std::ostringstream osstr;
    BadWordsFileFilter(isstr, osstr);
    REQUIRE(osstr.str() == string("hey dude, this is text!\nare you see that?\nэй,как дела?\n"));
}