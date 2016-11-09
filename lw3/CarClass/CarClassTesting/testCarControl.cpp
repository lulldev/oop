#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CarControlTesting

#include <boost/test/unit_test.hpp>

#include <sstream>

#include "Car.h"
#include "CarControl.h"

using namespace std;

struct RemoteControlDependencies
{
    CCar car;
    CCarControl carControl;
//    stringstream input;
//    stringstream output;
};

struct CarFixture
{
    CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car_control, RemoteControlDependencies)

    BOOST_AUTO_TEST_CASE(turn_on)
    {
        BOOST_CHECK(!car.IsEngineTurnOn());
        carControl.HandleCommand();
    }

BOOST_AUTO_TEST_SUITE_END()

