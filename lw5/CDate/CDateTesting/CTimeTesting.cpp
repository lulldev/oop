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

BOOST_AUTO_TEST_CASE(test_addition_operator)
{
    time = CTime(10, 10, 20) + CTime(5, 10, 20);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "15:20:40");
    
    time = CTime(23, 50, 00) + CTime(2, 30, 00);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "02:20:00");

    time = CTime(23, 59, 59) + CTime(0, 0, 3);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "00:00:02");
}

BOOST_AUTO_TEST_CASE(test_substraction_operator)
{
    time = CTime(10, 10, 20) - CTime(5, 20, 20);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "04:50:00");
    
    time = CTime(0, 0, 5) - CTime(0, 0, 10);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "23:59:55");
}

BOOST_AUTO_TEST_CASE(test_prefix_inc_and_dec)
{
    time = ++CTime(10, 10, 20);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "10:10:21");
    
    time = ++CTime(23, 59, 59);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "00:00:00");
    
    time = --CTime(10, 10, 20);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "10:10:19");
    
    time = --CTime(0, 0, 0);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "23:59:59");
}

BOOST_AUTO_TEST_CASE(test_postfix_inc_and_dec)
{
    time = CTime(10, 10, 20)++;
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "10:10:21");
    
    time = CTime(23, 59, 59)++;
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "00:00:00");
    
    time = CTime(10, 10, 20)--;
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "10:10:19");
    
    time = CTime(0, 0, 0)--;
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "23:59:59");
}

BOOST_AUTO_TEST_CASE(test_assignment_operator)
{
    CTime time1(10);
    CTime time2;
    time2 = time1;
    BOOST_REQUIRE(time1.m_timeSeconds == time2.m_timeSeconds);
}

BOOST_AUTO_TEST_CASE(test_assignment_addition_operator)
{
    CTime time1(50);
    CTime time2(100);
    time2 += time1;
    BOOST_REQUIRE(time2.m_timeSeconds == 150);
}

// todo: -=
// todo: *=
// todo: /=

BOOST_AUTO_TEST_CASE(test_comparison_operator)
{
    CTime time1(100);
    CTime time2(100);
    CTime time3(120);

    BOOST_REQUIRE(time1 != time3);
    BOOST_REQUIRE(time2 == time1);
}

BOOST_AUTO_TEST_CASE(test_strict_comparison_operator)
{
    CTime time1(100);
    CTime time2(100);
    CTime time3(120);
    
    BOOST_REQUIRE(time1 < time3);
    BOOST_REQUIRE(time3 > time1);
}

BOOST_AUTO_TEST_CASE(test_nonstrict_comparison_operator)
{
    CTime time1(100);
    CTime time2(100);
    CTime time3(120);
    
    BOOST_REQUIRE(time1 <= time2);
    BOOST_REQUIRE(time3 >= time1);
}

BOOST_AUTO_TEST_CASE(test_multiplication_operator)
{
    CTime time1(3, 5, 15);
    time = time1 * 3;
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "09:15:45");
    
    // todo
    //    CTime time2 = 3 * time1;
    //    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "09:15:45");
}

BOOST_AUTO_TEST_CASE(test_division_operator)
{
    CTime time1(9, 15, 40);
    CTime time2(3, 5, 13);
    time = time1 / time2;
    
    BOOST_REQUIRE(time.m_timeSeconds == 3);
    BOOST_REQUIRE((time1 / 3) == time2);
    
    time = (time1 / 2);
    BOOST_REQUIRE(time.FormatTime(time.m_timeSeconds) == "04:37:50");
}


BOOST_AUTO_TEST_SUITE_END()
