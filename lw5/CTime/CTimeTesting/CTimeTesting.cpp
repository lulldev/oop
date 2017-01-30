#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TimeTesting

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <sstream>

#include "CTime.h"

using namespace std;

struct TimeFixture
{
    CTime time;
};

bool VerifyTime(const CTime & time, unsigned hours, unsigned minutes, unsigned seconds)
{
    return ((time.GetHours() == hours) && (time.GetMinutes() == minutes) && (time.GetSeconds() == seconds));
}

BOOST_FIXTURE_TEST_SUITE(TimeTesting, TimeFixture)

BOOST_AUTO_TEST_CASE(test_init_wrong_time)
{
    BOOST_CHECK_THROW(CTime(40, 2, 10), invalid_argument);
    BOOST_CHECK_NO_THROW(CTime(10, 2, 10));
}

BOOST_AUTO_TEST_CASE(test_init_time)
{
    CTime time(2, 12, 10);
    CTime time1(100);
}

BOOST_AUTO_TEST_CASE(test_get_hours)
{
    CTime time(10, 20, 30);
    BOOST_CHECK_EQUAL(time.GetHours(), 10);
}

BOOST_AUTO_TEST_CASE(test_get_minutes)
{
    CTime time(0, 20, 30);
    BOOST_CHECK_EQUAL(time.GetMinutes(), 20);
}

BOOST_AUTO_TEST_CASE(test_get_seconds)
{
    CTime time(80);
    BOOST_CHECK_EQUAL(time.GetSeconds(), 20);
}

BOOST_AUTO_TEST_CASE(test_format_date_wrong_result)
{
    CTime time1(100);
    BOOST_CHECK(time1.FormatTime() != "00:00:10");
    
    CTime time2(200);
    BOOST_CHECK(time2.FormatTime() != "00:00:00");
}

BOOST_AUTO_TEST_CASE(test_format_date)
{
    CTime time1(10);
    BOOST_CHECK_EQUAL(time1.FormatTime(), "00:00:10");
    
    CTime time2(160);
    BOOST_CHECK_EQUAL(time2.FormatTime(), "00:02:40");
    
    CTime time3(3600);
    BOOST_CHECK_EQUAL(time3.FormatTime(), "01:00:00");
}

BOOST_AUTO_TEST_CASE(test_addition_operator_wrong_result)
{
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0) + CTime(10, 10, 20), 0, 0, 0));
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0) + CTime(10, 10, 20), 10, 10, 0));
}

BOOST_AUTO_TEST_CASE(test_addition_operator)
{
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0) + CTime(10, 10, 20), 0, 0, 0));

    BOOST_REQUIRE(VerifyTime(CTime(10, 10, 20) + CTime(5, 10, 20), 15, 20, 40));
    BOOST_REQUIRE(VerifyTime(CTime(23, 50, 00) + CTime(2, 30, 00), 2, 20, 0));
    BOOST_REQUIRE(VerifyTime(CTime(23, 59, 59) + CTime(0, 0, 3), 0, 0, 2));
}

BOOST_AUTO_TEST_CASE(test_substraction_operator_wrong_result)
{
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0) - CTime(10, 10, 20), 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_substraction_operator)
{
    BOOST_REQUIRE(VerifyTime(CTime(10, 10, 20) - CTime(5, 20, 20), 4, 50, 0));
    BOOST_REQUIRE(VerifyTime(CTime(0, 0, 5) - CTime(0, 0, 10), 23, 59, 55));
}

// clear
BOOST_AUTO_TEST_CASE(test_prefix_inc_and_dec_with_wrong)
{
    BOOST_REQUIRE(!VerifyTime(++CTime(0, 0, 10), 0, 0, 0));
    BOOST_REQUIRE(!VerifyTime(--CTime(0, 0, 10), 0, 0, 11));
}

BOOST_AUTO_TEST_CASE(test_prefix_inc_and_dec)
{
    BOOST_REQUIRE(VerifyTime(++CTime(10, 10, 20), 10, 10, 21));
    BOOST_REQUIRE(VerifyTime(--CTime(0, 0, 0), 23, 59, 59));
}

BOOST_AUTO_TEST_CASE(test_postfix_inc_and_dec_with_wrong)
{
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0)++, 0, 0, 1));
    BOOST_REQUIRE(!VerifyTime(CTime(0, 0, 0)--, 23, 59, 59));
}

BOOST_AUTO_TEST_CASE(test_postfix_inc_and_dec)
{    
    CTime time1(23, 59, 59);
    BOOST_REQUIRE(VerifyTime(time1++, 23, 59, 59));
    BOOST_REQUIRE(VerifyTime(time1, 0, 0, 0));
    
    BOOST_REQUIRE(VerifyTime(time1--, 0, 0, 0));
    BOOST_REQUIRE(VerifyTime(time1, 23, 59, 59));
}

BOOST_AUTO_TEST_CASE(test_assignment_operator)
{
    CTime time1(10);
    CTime time2 = time1;
    CTime time3(100);

    BOOST_REQUIRE(time1 != time3);
    BOOST_REQUIRE_EQUAL(VerifyTime(time1, 0, 0, 10), VerifyTime(time2, 0, 0, 10));
}

BOOST_AUTO_TEST_CASE(test_assignment_addition_operator_wrong_result)
{
    CTime time1(50);
    CTime time2(100);
    time2 += time1;
    
    BOOST_REQUIRE(!VerifyTime(time2, 0, 0, 10));
}

BOOST_AUTO_TEST_CASE(test_assignment_addition_operator)
{
    CTime time1(50);
    CTime time2(100);
    time2 += time1;
    
    BOOST_REQUIRE(VerifyTime(time2, 0, 2, 30));
}

BOOST_AUTO_TEST_CASE(test_assignment_subtraction_operator_wrong_result)
{
    CTime time1(250);
    CTime time2(50);
    time1 -= time2;
    
    BOOST_REQUIRE(!VerifyTime(time2, 0, 0, 10));
}

BOOST_AUTO_TEST_CASE(test_assignment_subtraction_operator)
{
    CTime time1(250);
    CTime time2(50);
    time1 -= time2;
    
    BOOST_REQUIRE(VerifyTime(time1, 0, 3, 20));
}

BOOST_AUTO_TEST_CASE(test_assignment_multiplocation_operator_wrong_result)
{
    CTime time1(10);
    CTime time2(10);
    time1 *= time2;
    
    BOOST_REQUIRE(!VerifyTime(time2, 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_assignment_multiplocation_operator)
{
    CTime time1(10);
    CTime time2(10);
    time1 *= time2;
    
    BOOST_REQUIRE(VerifyTime(time1, 0, 1, 40));
}


BOOST_AUTO_TEST_CASE(test_assignment_division_operator_with_wrong_param)
{
    CTime time1(100);
    CTime time2(0);
    CTime time3(10);
    
    BOOST_CHECK_THROW(time1 / time2, overflow_error);
}

BOOST_AUTO_TEST_CASE(test_assignment_division_operator)
{
    CTime time1(100);
    CTime time2(10);
    
    time1 /= time2;
    
    BOOST_REQUIRE(VerifyTime(time1, 0, 0, 10));
}

BOOST_AUTO_TEST_CASE(test_comparison_operator)
{
    CTime time1(10);
    CTime time2(20);
    CTime time3(10);

    BOOST_REQUIRE(!(time1 == time2));
    BOOST_REQUIRE(time1 == time1);
    BOOST_REQUIRE(time1 == time3);
    
    BOOST_REQUIRE(!(time1 != time3));
    BOOST_REQUIRE(time1 != time2);
}

BOOST_AUTO_TEST_CASE(test_strict_comparison_operator)
{
    CTime time1(10);
    CTime time2(40);
    CTime time3(20);
    
    BOOST_REQUIRE(!(time1 > time1));
    BOOST_REQUIRE(!(time1 < time1));
    BOOST_REQUIRE(!(time3 < time1));
    BOOST_REQUIRE(!(time1 > time3));
    
    BOOST_REQUIRE(time3 > time1);
    BOOST_REQUIRE(time1 < time2);
}

BOOST_AUTO_TEST_CASE(test_nonstrict_comparison_operator)
{
    CTime time1(50);
    CTime time2(60);
    CTime time3(60);
    
    BOOST_REQUIRE(!(time1 >= time2));
    BOOST_REQUIRE(!(time2 <= time1));

    BOOST_REQUIRE(time1 <= time2);
    BOOST_REQUIRE(time2 >= time1);
    BOOST_REQUIRE(time2 >= time3);
    BOOST_REQUIRE(time2 <= time3);

}

BOOST_AUTO_TEST_CASE(test_multiplication_operator_wrong_result)
{
    BOOST_REQUIRE(!VerifyTime(CTime (3, 5, 15) * 2, 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_multiplication_operator)
{
    BOOST_REQUIRE(VerifyTime(CTime(3, 5, 15) * 0, 0, 0, 0));
    BOOST_REQUIRE(VerifyTime(CTime(3, 5, 15) * 3, 9, 15, 45));
    BOOST_REQUIRE(VerifyTime(3 * CTime(3, 5, 15), 9, 15, 45));
    BOOST_REQUIRE(VerifyTime(CTime(23, 0, 0) * 3, 21, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_division_operator_wrong_param)
{
    CTime time1(100);
    BOOST_CHECK_THROW(CTime(100) / 0, overflow_error);
}

BOOST_AUTO_TEST_CASE(test_division_operator_wrong_vals)
{
    BOOST_CHECK_THROW(CTime(100) / CTime(0), overflow_error);
}

BOOST_AUTO_TEST_CASE(test_division_operator)
{
    BOOST_REQUIRE_EQUAL(CTime(100) / CTime(10), 10);
    BOOST_REQUIRE_EQUAL(CTime(100) / CTime(100), 1);
    BOOST_REQUIRE_EQUAL(CTime(10) / CTime(100), 0);
    BOOST_REQUIRE_EQUAL(CTime(1, 0, 0) / CTime(2, 0, 0), 0);
}


BOOST_AUTO_TEST_CASE(test_output_time)
{
    CTime time1(10);
    std::stringstream output;
    output << time1;
    BOOST_REQUIRE_EQUAL(output.str(), "00:00:10");
    output.clear();
}

BOOST_AUTO_TEST_CASE(test_input_wrong_time)
{
    CTime time1;
    std::stringstream input1("");
    std::stringstream input2("00:00");
    std::stringstream input3("00:00;00");
    std::stringstream input4("some text");

    BOOST_CHECK_EQUAL(input1 >> time1, "INVALID TIME");
    BOOST_CHECK_EQUAL(input2 >> time1, "INVALID TIME");
    BOOST_CHECK_EQUAL(input3 >> time1, "INVALID TIME");
    BOOST_CHECK_EQUAL(input4 >> time1, "INVALID TIME");
}

BOOST_AUTO_TEST_CASE(test_input_time)
{
    CTime time1;
    CTime time2;

    std::stringstream input1("00:00:10");
    std::stringstream input2("12:20:10");

    input1 >> time1;
    VerifyTime(time, 0, 0, 10);
    
    input2 >> time2;
    VerifyTime(time, 12, 20, 10);
}

BOOST_AUTO_TEST_SUITE_END()
