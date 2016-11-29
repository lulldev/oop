#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TimeTesting

#include <iostream>
#include <boost/test/unit_test.hpp>

#include "CTime.h"

using namespace std;

struct TimeFixture
{
    CTime time;
};

BOOST_FIXTURE_TEST_SUITE(DateTesting, TimeFixture)

BOOST_AUTO_TEST_CASE(test_init_date)
{
    CTime time1(40, 2, 10);
    BOOST_CHECK(time1.IsValid() == false);
    
    CTime time2(0, 0, 0);
    BOOST_CHECK(time2.IsValid() == true);
    
    CTime time3(2, 12, 10);
    BOOST_CHECK(time2.IsValid() == true);
    
}

BOOST_AUTO_TEST_CASE(test_get_hours)
{
    CTime time(10, 20, 30);
    BOOST_CHECK(time.GetHours() == 10);
}

BOOST_AUTO_TEST_CASE(test_get_minutes)
{
    CTime time(0, 20, 30);
    BOOST_CHECK(time.GetMinutes() == 20);
}

BOOST_AUTO_TEST_CASE(test_get_seconds)
{
    CTime time(80);
    BOOST_CHECK(time.GetSeconds() == 20);
}

BOOST_AUTO_TEST_CASE(test_format_date)
{
    BOOST_CHECK(time.FormatTime(10) == "00:00:10");
    BOOST_CHECK(time.FormatTime(160) == "00:02:40");
    BOOST_CHECK(time.FormatTime(3600) == "01:00:00");
    BOOST_CHECK(time.FormatTime(5432) == "01:30:32");
}

BOOST_AUTO_TEST_CASE(test_parse_seconds_from_format_date)
{
    string formatTime("strng");
    BOOST_CHECK(time.ParseSecondsFromFormatTime(formatTime) == -1);
    
    string formatTime2("01:01");
    BOOST_CHECK(time.ParseSecondsFromFormatTime(formatTime2) == -1);
    
    string formatTime3("03:40:20");
    BOOST_CHECK(time.ParseSecondsFromFormatTime(formatTime3) == 13220);
    
    string formatTime4("00:00:20");
    BOOST_CHECK(time.ParseSecondsFromFormatTime(formatTime4) == 20);
}

BOOST_AUTO_TEST_SUITE_END()
